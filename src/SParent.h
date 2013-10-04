/*
 * SParent.h
 *
 *  Created on: 2013-8-25
 *      Author: casa
 */

#ifndef SPARENT_H_
#define SPARENT_H_

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>

class SParent {
public:
	SParent();
	virtual ~SParent();

	virtual void f1()=0;

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, const unsigned int version){

	}
};

#endif /* SPARENT_H_ */
