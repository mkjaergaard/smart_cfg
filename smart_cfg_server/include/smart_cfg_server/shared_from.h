#ifndef __SHARED_FROM_H_INCLUDED__
#define __SHARED_FROM_H_INCLUDED__

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <vector>

template<typename T>
class SharedFrom
{
public:
  typedef boost::shared_ptr<T> Ptr;
  typedef boost::shared_ptr<const T> ConstPtr;
  typedef boost::weak_ptr<T> WeakPtr;
  typedef boost::weak_ptr<const T> WeakConstPtr;

  typedef std::vector<WeakConstPtr> WeakConstPtrList;
};

#endif
