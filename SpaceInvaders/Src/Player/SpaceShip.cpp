#include "SpaceShip.h"
#include "../Utils/ExtensionFunctions.h"
#include "../Utils/VectorHelpers.h"
#include "../Scenes/MainScene.h"
#include <iostream>

namespace Player
{
	SpaceShip::SpaceShip()
	{
		this->_window_width = GetScreenWidth();
		this->_window_height = GetScreenHeight();

		this->_position = {
			static_cast<float>(this->_window_width) / 2,
			static_cast<float>(this->_window_height) - this->_base_height - 7
		};
		this->_velocity = {0, 0};

		this->_god_mode = false;
		this->_bullet_type = Enums::BulletType::SingleBullet;
	}

	SpaceShip::~SpaceShip()
	{
		for (auto& _bullet : this->_bullets)
			delete _bullet;

		this->_bullets.clear();
	}

	void SpaceShip::show()
	{
		const auto bodyColor = Utils::ExtensionFunctions::LerpColor(
			this->_zero_health_color,
			this->_space_ship_color,
			this->_health / 100.0f
		);

		const auto x = this->_position.x;
		const auto y = this->_position.y;

		this->_ship_points[11] = {x - this->_shooter_width / 2.0f, y - this->_base_height * 2};
		this->_ship_points[10] = {x + this->_shooter_width / 2.0f, y - this->_base_height * 2};
		this->_ship_points[9] = {x + this->_shooter_width / 2.0f, y - this->_base_height * 1.5f};
		this->_ship_points[8] = {x + this->_base_width / 4.0f, y - this->_base_height * 1.5f};
		this->_ship_points[7] = {x + this->_base_width / 4.0f, y - this->_base_height / 2.0f};
		this->_ship_points[6] = {x + this->_base_width / 2.0f, y - this->_base_height / 2.0f};
		this->_ship_points[5] = {x + this->_base_width / 2.0f, y + this->_base_height / 2.0f};
		this->_ship_points[4] = {x - this->_base_width / 2.0f, y + this->_base_height / 2.0f};
		this->_ship_points[3] = {x - this->_base_width / 2.0f, y - this->_base_height / 2.0f};
		this->_ship_points[2] = {x - this->_base_width / 4.0f, y - this->_base_height / 2.0f};
		this->_ship_points[1] = {x - this->_base_width / 4.0f, y - this->_base_height * 1.5f};
		this->_ship_points[0] = {x - this->_shooter_width / 2.0f, y - this->_base_height * 1.5f};

		DrawPolyExLines(this->_ship_points, this->_ship_points_count, bodyColor);

		Color currentColor;
		if (this->_health < 50)
			currentColor = Utils::ExtensionFunctions::LerpColor(
				this->_zero_health_color,
				this->_half_health_color,
				this->_health / 50.0f
			);
		else
			currentColor = Utils::ExtensionFunctions::LerpColor(
				this->_half_health_color,
				this->_full_health_color,
				(this->_health - 50) / 50.0f
			);

		DrawRectangle(0, this->_window_height - 7,
		              this->_window_width * this->_health / 100, 10, currentColor);
	}

	void SpaceShip::update()
	{
		if (!IsKeyDown(KEY_SPACE) || this->_current_shoot_wait_time < 0)
			this->_current_shoot_wait_time = this->_min_shoot_wait_time;

		if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_RIGHT))
		{
			// Do Nothing When Both Keys Are Pressed
		}
		else if (IsKeyDown(KEY_LEFT))
			this->moveShip(Enums::Direction::Left);
		else if (IsKeyDown(KEY_RIGHT))
			this->moveShip(Enums::Direction::Right);

		if (IsKeyDown(KEY_SPACE))
			this->shootBullets();

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
				i -= 1;
			}
		}
	}

	void SpaceShip::moveShip(const Enums::Direction direction)
	{
		if (this->_position.x < this->_base_width / 2.0f)
			this->_position.x = this->_base_width / 2.0f + 1;

		if (this->_position.x > this->_window_width - this->_base_width / 2.0f)
			this->_position.x = this->_window_width - this->_base_width / 2.0f - 1;

		this->_velocity = { static_cast<float>(this->_window_width), 0};
		if (direction == Enums::Direction::Left)
			this->_velocity = Utils::VectorHelpers::SetMag(this->_velocity, -this->_speed);
		else
			this->_velocity = Utils::VectorHelpers::SetMag(this->_velocity, this->_speed);

		this->_position = Utils::VectorHelpers::Add(this->_position,
		                                            Utils::VectorHelpers::Mult(this->_velocity, GetFrameTime()));
	}

	void SpaceShip::setBulletType(Enums::BulletType bulletType)
	{
		this->_bullet_type = bulletType;
	}

	std::vector<Common::Bullet*> SpaceShip::getBullets() const
	{
		std::vector<Common::Bullet*> bullets;

		switch (this->_bullet_type)
		{
		case Enums::BulletType::SingleBullet:
			bullets.push_back(new Common::Bullet(
				this->_position.x - this->_shooter_width / 2.0f,
				this->_position.y - this->_base_height * 1.5f,
				this->_base_width / 10,
				true,
				RED
			));
			break;

		case Enums::BulletType::DoubleBullet:
			for (int i = 0; i < 2; i++)
			{
				float offsetPos;
				if (i == 0)
					offsetPos = this->_shooter_width * 0.5f;
				else
					offsetPos = 1.5f * -this->_shooter_width;

				bullets.push_back(new Common::Bullet(
					this->_position.x + offsetPos,
					this->_position.y - this->_base_height * 1.5f,
					this->_base_width / 10,
					true,
					DARKBLUE
				));
			}
			break;

		case Enums::BulletType::SprayBullet:
			for (int i = 0; i < 80; i += 10)
			{
				bullets.push_back(new Common::Bullet(
					this->_position.x,
					this->_position.y - this->_base_height * 1.5f,
					this->_base_width / 10,
					true,
					YELLOW,
					-40 + i
				));
			}
			break;
		}

		return bullets;
	}

	void SpaceShip::shootBullets()
	{
		if (this->_current_shoot_wait_time == this->_min_shoot_wait_time)
		{
			std::vector<Common::Bullet*> bullets = this->getBullets();
			this->_bullets.insert(this->_bullets.end(), bullets.begin(), bullets.end());
		}

		this->_current_shoot_wait_time -= GetFrameTime();
	}

	void SpaceShip::decreaseHealth(float amount)
	{
		if (!this->_god_mode)
			this->_health -= amount;
	}

	void SpaceShip::activateGodMode()
	{
		this->_god_mode = true;
	}

	bool SpaceShip::isDestroyed()
	{
		if (this->_health <= 0)
		{
			this->_health = 0;
			return true;
		}

		return false;
	}

	void SpaceShip::resetSpaceShip()
	{
		for (auto& _bullet : this->_bullets)
			delete _bullet;
		this->_bullets.clear();

		this->_current_shoot_wait_time = this->_min_shoot_wait_time;
		this->_health = 100;
		this->_god_mode = false;
		this->_bullet_type = Enums::BulletType::SingleBullet;
	}

	void SpaceShip::checkEnemyCollisionWithBullet(Enemies::Enemy* enemy, int enemyIndex)
	{
		for (std::size_t i = 0; i < this->_bullets.size(); i++)
		{
			if (enemy->isEnemyHit(this->_bullets[i]->getPosition()))
			{
				const auto enemyDead = enemy->checkDeathAndTakeDamage();

				if (enemyDead)
					Scenes::MainScene::destroyEnemy(enemyIndex);

				delete this->_bullets[i];
				this->_bullets.erase(this->_bullets.begin() + i);
				i = i == 0 ? 0 : i - 1;
			}
		}
	}

	bool SpaceShip::didSpaceShipCollide(const Vector2 point) const
	{
		// ray-casting algorithm based on
		// http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html

		const auto x = point.x;
		const auto y = point.y;

		auto inside = false;
		for (auto i = 0, j = this->_ship_points_count - 1; i < this->_ship_points_count; j = i++)
		{
			const auto xi = this->_ship_points[i].x;
			const auto yi = this->_ship_points[i].y;
			const auto xj = this->_ship_points[j].x;
			const auto yj = this->_ship_points[j].y;

			const auto intersect = ((yi > y) != (yj > y)) &&
				(x < (xj - xi) * (y - yi) / (yj - yi) + xi);
			if (intersect) inside = !inside;
		}

		return inside;
	}

	Vector2 SpaceShip::getSpaceShipPosition() const
	{
		return this->_position;
	}
}
