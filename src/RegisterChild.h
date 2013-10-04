/*
 * RegisterChild.h
 *
 *  Created on: 2013-8-25
 *      Author: casa
 */

#ifndef REGISTERCHILD_H_
#define REGISTERCHILD_H_

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "SChild1.h"

//#pragma auto_inline
template<class Archive>
void Register_children(Archive &ar){
	ar.register_type(static_cast<SChild1 *>(NULL));
	ar.register_type(static_cast<SChild *>(NULL));
}

#endif /* REGISTERCHILD_H_ */
