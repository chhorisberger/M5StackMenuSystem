#ifndef DOWN_SOFT_KEY_H
#define DOWN_SOFT_KEY_H


#include "SoftKey.h"

class DownSoftKey : virtual public SoftKey
{
public:
	DownSoftKey(SoftKeySlot slot_);
	virtual ~DownSoftKey() {}

protected:
	virtual void renderInternal(int x, int y, int w, int h);

private:
	void renderIcon(int x, int y, int w, int h);
};

#endif 

