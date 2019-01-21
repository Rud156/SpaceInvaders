#include "SpaceShip.h"
#include "../Utils/ExtensionFunctions.h"
#include "../Utils/ColorHelpers.h"
#include "../Utils/VectorHelpers.h"
#include "../Scenes/MainScene.h"

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
		this->_health = this->_max_health;

		this->_shoot_sound = LoadSound("resources/audio/shoot.wav");
	}

	SpaceShip::~SpaceShip()
	{
		UnloadSound(this->_shoot_sound);

		for (auto& _bullet : this->_bullets)
			delete _bullet;

		this->_bullets.clear();
	}

	void SpaceShip::show()
	{
		const auto bodyColor = Utils::ColorHelpers::LerpColor(
			this->_zero_health_color,
			this->_space_ship_color,
			this->_health / this->_max_health
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
		const auto healthRatio = this->_health / this->_max_health;

		if (healthRatio <= 0.5f)
			currentColor = Utils::ColorHelpers::LerpColor(
				this->_zero_health_color,
				this->_half_health_color,
				healthRatio * 2
			);
		else
			currentColor = Utils::ColorHelpers::LerpColor(
				this->_half_health_color,
				this->_full_health_color,
				(healthRatio - 0.5f) * 2.0f
			);

		DrawRectangle(0, this->_window_height - 7,
		              this->_window_width * healthRatio, 10, currentColor);


		if (this->_god_mode)
		{
			const auto godModeTextWidth = MeasureText(this->_god_mode_text, 20);
			DrawText(this->_god_mode_text, this->_window_width - godModeTextWidth - 20,
			         this->_window_height - 30, 20, PURPLE);
		}
	}

	void SpaceShip::update()
	{
		if (!IsKeyDown(KEY_SPACE) || this->_current_shoot_wait_time < 0)
			this->_current_shoot_wait_time = this->_min_shoot_wait_time;

		if (IsKeyDown(KEY_G) && IsKeyDown(KEY_O) && IsKeyDown(KEY_D))
			this->activateGodMode();

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

		this->_velocity = {static_cast<float>(this->_window_width), 0};
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
				Utils::ColorHelpers::CollectibleTypeToColor(Enums::BulletType::SingleBullet)
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
					Utils::ColorHelpers::CollectibleTypeToColor(Enums::BulletType::DoubleBullet)
				));
			}
			break;

		case Enums::BulletType::SprayBullet:
			for (int i = 0; i < 80; i += 10)
			{
				bullets.push_back(new Common::Bullet(
					this->_position.x - this->_shooter_width / 2.0f,
					this->_position.y - this->_base_height * 1.5f,
					this->_base_width / 10,
					true,
					Utils::ColorHelpers::CollectibleTypeToColor(Enums::BulletType::SprayBullet),
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
			PlaySound(this->_shoot_sound);
			std::vector<Common::Bullet*> bullets = this->getBullets();
			this->_bullets.insert(this->_bullets.end(), bullets.begin(), bullets.end());
		}

		this->_current_shoot_wait_time -= GetFrameTime();
	}

	bool SpaceShip::decreaseHealthAndCheckDeath(const float amount)
	{
		if (!this->_god_mode)
			this->_health -= amount;

		return this->_health < 0;
	}

	void SpaceShip::activateGodMode()
	{
		this->_god_mode = true;
	}

	void SpaceShip::resetSpaceShip()
	{
		for (auto& _bullet : this->_bullets)
			delete _bullet;
		this->_bullets.clear();

		this->_current_shoot_wait_time = this->_min_shoot_wait_time;
		this->_health = this->_max_health;
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
