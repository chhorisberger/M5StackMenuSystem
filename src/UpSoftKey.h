#ifndef UP_SOFT_KEY_H
#define UP_SOFT_KEY_H


#include "SoftKey.h"

class UpSoftKey : virtual public SoftKey
{
public:
	UpSoftKey(SoftKeySlot slot_, Layout& layout_, Control& control_, Display& display_);
	virtual ~UpSoftKey() {}

protected:
	virtual void renderInternal(int x, int y, int w, int h);

private:
	void renderIcon(int x, int y, int w, int h);
};

#endif 

