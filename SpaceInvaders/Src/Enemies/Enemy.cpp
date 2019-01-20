#include "Enemy.h"
#include "../Utils/ExtensionFunctions.h"
#include "../Utils/VectorHelpers.h"
#include "../Utils/ColorHelpers.h"
#include "../Scenes/MainScene.h"

namespace Enemies
{
	Enemy::Enemy(float xPosition, float yPosition, float enemyBaseWidth)
	{
		this->_position = {xPosition, yPosition};
		this->_prev_x = this->_position.x;

		this->_screen_width = GetScreenWidth();
		this->_screen_height = GetScreenHeight();

		this->_position_to_reach = {
			static_cast<float>(GetRandomValue(0, this->_screen_width)),
			static_cast<float>(GetRandomValue(0, this->_screen_height / 2))
		};

		this->_velocity = {0, 0};
		this->_acceleration = {0, 0};

		this->_base_width = enemyBaseWidth;
		this->_base_height = this->_base_width / 5;
		this->_shooter_height = this->_base_width * 3 / 20;

		this->_current_shoot_wait_time = this->_min_shoot_wait_time;
		this->_max_health = 100 * enemyBaseWidth / 45;
		this->_current_health = this->_max_health;

		std::random_device rd;
		this->_gen = std::mt19937(rd());
		this->_dis = std::uniform_real_distribution<float>(0, 1);
	}

	Enemy::~Enemy()
	{
		for (auto& _bullet : this->_bullets)
			delete _bullet;

		this->_bullets.clear();
	}

	void Enemy::show()
	{
		Color currentColor;
		const auto mappedHealth = Utils::ExtensionFunctions::Map(this->_current_health,
		                                                         0, this->_max_health, 0, 100);
		if (mappedHealth < 50)
			currentColor = Utils::ColorHelpers::LerpColor(this->_zero_health_color,
			                                              this->_half_health_color, mappedHealth / 50.0f);
		else
			currentColor = Utils::ColorHelpers::LerpColor(this->_half_health_color,
			                                              this->_full_health_color, (mappedHealth - 50) / 50.0f);

		const float x = this->_position.x;
		const float y = this->_position.y;

		this->_ship_shape_points[0] = {x - this->_base_width / 2, y - this->_base_height * 1.5f};
		this->_ship_shape_points[1] = {x - this->_base_width / 2 + this->_base_height, y - this->_base_height * 1.5f};
		this->_ship_shape_points[2] = {x - this->_base_width / 2 + this->_base_height, y - this->_base_height / 2};
		this->_ship_shape_points[3] = {x + this->_base_width / 2 - this->_base_height, y - this->_base_height / 2};
		this->_ship_shape_points[4] = {x + this->_base_width / 2 - this->_base_height, y - this->_base_height * 1.5f};
		this->_ship_shape_points[5] = {x + this->_base_width / 2, y - this->_base_height * 1.5f};
		this->_ship_shape_points[6] = {x + this->_base_width / 2, y + this->_base_height / 2};
		this->_ship_shape_points[7] = {x + this->_base_width / 2 - this->_base_width / 5, y + this->_base_height / 2};
		this->_ship_shape_points[8] = {
			x + this->_base_width / 2 - this->_base_width / 5, y + this->_base_height * 1.5f
		};
		this->_ship_shape_points[9] = {
			x + this->_base_width / 2 - this->_base_width / 5 - this->_base_width / 5, y + this->_base_height * 1.5f
		};
		this->_ship_shape_points[10] = {
			x + this->_base_width / 2 - this->_base_width / 5 - this->_base_width / 5,
			y + this->_base_height * 1.5f + this->_shooter_height
		};
		this->_ship_shape_points[11] = {
			x - this->_base_width / 2 + this->_base_width / 5 + this->_base_width / 5,
			y + this->_base_height * 1.5f + this->_shooter_height
		};
		this->_ship_shape_points[12] = {
			x - this->_base_width / 2 + this->_base_width / 5 + this->_base_width / 5, y + this->_base_height * 1.5f
		};
		this->_ship_shape_points[13] = {
			x - this->_base_width / 2 + this->_base_width / 5, y + this->_base_height * 1.5f
		};
		this->_ship_shape_points[14] = {x - this->_base_width / 2 + this->_base_width / 5, y + this->_base_height / 2};
		this->_ship_shape_points[15] = {x - this->_base_width / 2, y + this->_base_height / 2};
		this->_ship_shape_points[16] = {x - this->_base_width / 2, y - this->_base_height * 1.5f};

		DrawPolyExLines(this->_ship_shape_points, this->_ship_shape_points_count, currentColor);
	}

	void Enemy::update()
	{
		this->_prev_x = this->_position.x;

		this->_velocity = Utils::VectorHelpers::Add(this->_velocity, this->_acceleration);
		this->_velocity = Utils::VectorHelpers::Limit(this->_velocity, this->_max_speed);

		this->_position = Utils::VectorHelpers::Add(this->_position,
		                                            Utils::VectorHelpers::Mult(this->_velocity, GetFrameTime()));
		this->_acceleration = Utils::VectorHelpers::Mult(this->_acceleration, 0);

		if (Utils::VectorHelpers::Mag(this->_velocity) <= 1)
		{
			this->_position_to_reach = {
				static_cast<float>(GetRandomValue(0, this->_screen_width)),
				static_cast<float>(GetRandomValue(0, this->_screen_height / 2))
			};
		}

		for (auto bullet : this->_bullets)
		{
			bullet->show();
			bullet->update();
		}

		for (std::size_t i = 0; i < this->_bullets.size(); i++)
		{
			if (this->_bullets[i]->isOutOfScreen())
			{
				delete this->_bullets[i];
				this->_bullets.erase(this->_bullets.begin() + i);
				i = -1;
			}
		}

		this->checkTargetPointReached();
	}

	void Enemy::checkTargetPointReached()
	{
		auto desired = Utils::VectorHelpers::Sub(this->_position_to_reach, this->_position);
		const auto desiredMag = Utils::VectorHelpers::Mag(desired);

		if (desiredMag < this->_magnitude_limit)
		{
			const auto mappedSpeed = Utils::ExtensionFunctions::Map(desiredMag, 0, 50,
			                                                        0, this->_max_speed);
			desired = Utils::VectorHelpers::SetMag(desired, mappedSpeed);
		}
		else
			desired = Utils::VectorHelpers::SetMag(desired, this->_max_speed);

		auto steering = Utils::VectorHelpers::Sub(desired, this->_velocity);
		steering = Utils::VectorHelpers::Limit(steering, this->_max_force);

		this->_acceleration = Utils::VectorHelpers::Add(this->_acceleration, steering);
	}

	void Enemy::renderBullets()
	{
		if (this->_current_shoot_wait_time == this->_min_shoot_wait_time)
		{
			const float randomValue = this->_dis(this->_gen);
			if (randomValue < 0.5f)
			{
				this->_bullets.push_back(
					new Common::Bullet(
						this->_prev_x - this->_shooter_height / 2.0f,
						this->_position.y + this->_base_height * 5,
						this->_base_width / 5,
						false
					)
				);
			}
		}
	}

	void Enemy::checkAndShootIfNearPlayer(Vector2 playerPosition)
	{
		if (this->_current_shoot_wait_time < 0)
			this->_current_shoot_wait_time = this->_min_shoot_wait_time;

		const auto xPositionDistance = std::abs(playerPosition.x - this->_position.x);
		if (xPositionDistance < 200)
			this->renderBullets();
		else
			this->_current_shoot_wait_time = this->_min_shoot_wait_time;

		this->_current_shoot_wait_time -= GetFrameTime();
	}

	void Enemy::checkPlayerCollisionWithBullet(Player::SpaceShip* player)
	{
		for (std::size_t i = 0; i < this->_bullets.size(); i++)
		{
			if (player->didSpaceShipCollide(this->_bullets[i]->getPosition()))
			{
				const auto isPlayerDead = player->decreaseHealthAndCheckDeath
					(2 * this->_base_width / 10);

				if (isPlayerDead)
					Scenes::MainScene::destroyPlayer();

				delete this->_bullets[i];
				this->_bullets.erase(this->_bullets.begin() + i);
				i = i == 0 ? 0 : i - 1;
			}
		}
	}

	bool Enemy::checkDeathAndTakeDamage()
	{
		this->_current_health -= 20;
		return this->_current_health < 0;
	}

	bool Enemy::isEnemyHit(const Vector2 point) const
	{
		// ray-casting algorithm based on
		// http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html

		const auto x = point.x;
		const auto y = point.y;

		auto inside = false;
		for (auto i = 0, j = this->_ship_shape_points_count - 1; i < this->_ship_shape_points_count; j = i++)
		{
			const auto xi = this->_ship_shape_points[i].x;
			const auto yi = this->_ship_shape_points[i].y;
			const auto xj = this->_ship_shape_points[j].x;
			const auto yj = this->_ship_shape_points[j].y;

			const auto intersect = ((yi > y) != (yj > y)) &&
				(x < (xj - xi) * (y - yi) / (yj - yi) + xi);
			if (intersect) inside = !inside;
		}

		return inside;
	}

	Vector2 Enemy::getEnemyPosition() const
	{
		return this->_position;
	}

	float Enemy::getEnemyBaseWidth() const
	{
		return this->_base_width;
	}
}
