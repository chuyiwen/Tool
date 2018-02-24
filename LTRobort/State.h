#ifndef _STATE_H_
#define _STATE_H_


template<typename entity_type>
class State
{
public:
	virtual ~State(){}
	
	virtual void Enter(entity_type*) = 0;

	virtual void Update(entity_type*) = 0; 

	virtual void Exit(entity_type*) = 0;


};

#endif