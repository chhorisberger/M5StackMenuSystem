#ifndef CONTROL_H
#define CONTROL_H

class Control
{
	public:
		Control();

		void init();
		void loop();

		// TODO: create getters?
		bool buttonAPressed;
		bool buttonAReleased;
		bool buttonBPressed;
		bool buttonBReleased;
		bool buttonCPressed;
		bool buttonCReleased;

	private:
		void clearState();
		void checkButtons();
		void checkTouch();

};

#endif 

