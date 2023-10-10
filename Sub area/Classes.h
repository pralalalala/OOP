#pragma once

#pragma once

class Classes {
public:

	class Component {
	public:
		virtual ~Component() {}
		virtual int Operation() const = 0;
	};

	class DK :public Component {
	public:
		int Operation() const override { return 0; }
	};
	class fire :public Component {
	public:
		int Operation() const override { return 42; }
	};


	class Battle_Move_Assets
	{
	public:
		virtual void Mag_attack() = 0;
		virtual void Phis_attack() = 0;
		virtual bool Block_Attack() = 0;
		virtual bool Dodge_Attack() = 0;
	};

	class Move_Results : public Battle_Move_Assets
	{
		int HP, Stamina;
	public:
		/*virtual*/
		bool Block_Attack()
		{
			if (Stamina > 10) return true;
			else return false;
		}

		bool Dodge_Attack()
		{
			if (HP > 30) return true;
			else return false;
		}
	};

	class Decorator : public Battle_Move_Assets  
	{
		Battle_Move_Assets* BMA;
	public:
		Decorator(Battle_Move_Assets* w)
		{
			BMA = w;
		}

		/*virtual*/
		bool Dodge_Attack()
		{
			BMA->Dodge_Attack(); // делегирование
		}
	};
};
