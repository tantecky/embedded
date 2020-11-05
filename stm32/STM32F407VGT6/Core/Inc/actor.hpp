#ifndef E9C2DCFF_D736_498B_8D73_C958443B3727
#define E9C2DCFF_D736_498B_8D73_C958443B3727

template <typename T>
class Actor
{
public:
    virtual ~Actor()
    {
    }

    virtual void setValue(const T) = 0;
    virtual const T getMinValue() const = 0;
    virtual const T getMaxValue() const = 0;
};

#endif /* E9C2DCFF_D736_498B_8D73_C958443B3727 */
