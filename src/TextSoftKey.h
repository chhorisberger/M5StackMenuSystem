#ifndef TEXT_SOFT_KEY_H
#define TEXT_SOFT_KEY_H


#include "SoftKey.h"

class TextSoftKey : virtual public SoftKey
{
public:
	TextSoftKey(SoftKeySlot slot_, String text_);
	virtual ~TextSoftKey() {}

protected:
	virtual void renderInternal(int x, int y, int w, int h);

private:
	String text;

	void renderText(int x, int y, int w, int h);
};

#endif 

