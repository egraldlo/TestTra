/*
 * Schema.h
 *
 *  Created on: 2013-8-27
 *      Author: casa
 */

#ifndef SCHEMA_H_
#define SCHEMA_H_

class Schema {
public:
	Schema();
	virtual ~Schema();


};

class Schema_fix:public Schema{
public:

};

class Schema_variable:public Schema{
public:

};

#endif /* SCHEMA_H_ */
