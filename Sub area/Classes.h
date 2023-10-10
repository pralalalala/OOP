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


};