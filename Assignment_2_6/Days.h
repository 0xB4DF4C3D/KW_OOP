#pragma once
#include "OOP.h"

namespace CDays {

	class Wed : public OOP {
	public:
		Wed();
		~Wed();

		void PrintTitle(int num) override;
	};

	class Thu : public OOP {
	public:
		Thu();
		~Thu();

		void PrintTitle(int num) override;
	};

	class Fri : public OOP {
	public:
		Fri();
		~Fri();

		void PrintTitle(int num) override;
	};

	class None : public OOP {
	public:
		None();
		~None();

		void PrintTitle(int num) override;
	};

}