/*
 *	engine/core/ManagedObject.h generated by engine3 IDL compiler 0.60
 */

#ifndef MANAGEDOBJECT_H_
#define MANAGEDOBJECT_H_

#include "engine/orb/DistributedObjectBroker.h"

#include "engine/core/ManagedReference.h"

#include "system/thread/ReadWriteLock.h"

#include "system/io/Serializable.h"

#include "system/io/ObjectInputStream.h"

#include "system/io/ObjectOutputStream.h"

namespace engine {
namespace core {

class ManagedObject : public DistributedObjectStub {
public:
	void lock(bool doLock = true);

	void lock(ManagedObject* obj);

	void rlock(bool doLock = true);

	void wlock(bool doLock = true);

	void wlock(ManagedObject* obj);

	void unlock(bool doLock = true);

	void runlock(bool doLock = true);

	void setLockName(const String& name);

	void writeObject(String& data);

	void writeObject(ObjectOutputStream* stream);

	void readObject(const String& data);

	void readObject(ObjectInputStream* stream);

protected:
	ManagedObject(DummyConstructorParameter* param);

	virtual ~ManagedObject();

	void _lock(bool doLock = true);

	void _lock(ManagedObject* obj);

	void _rlock(bool doLock = true);

	void _wlock(bool doLock = true);

	void _wlock(ManagedObject* obj);

	void _unlock(bool doLock = true);

	void _runlock(bool doLock = true);

	void _setLockName(const String& name);

	friend class ManagedObjectHelper;
};

class ManagedObjectImplementation : public DistributedObjectServant, public Serializable {

public:
	ManagedObjectImplementation();
	ManagedObjectImplementation(DummyConstructorParameter* param);

	void lock(bool doLock = true);

	void lock(ManagedObject* obj);

	void rlock(bool doLock = true);

	void wlock(bool doLock = true);

	void wlock(ManagedObject* obj);

	void unlock(bool doLock = true);

	void runlock(bool doLock = true);

	void setLockName(const String& name);

	virtual void writeObject(String& data);

	virtual void writeObject(ObjectOutputStream* stream);

	virtual void readObject(const String& data);

	virtual void readObject(ObjectInputStream* stream);

	ManagedObject* _this;

	operator const ManagedObject*();

	DistributedObjectStub* _getStub();
protected:
	virtual ~ManagedObjectImplementation();

	void _setStub(DistributedObjectStub* stub);

	void _serializationHelperMethod();

	friend class ManagedObject;
};

class ManagedObjectAdapter : public DistributedObjectAdapter {
public:
	ManagedObjectAdapter(ManagedObjectImplementation* impl);

	Packet* invokeMethod(sys::uint32 methid, DistributedMethod* method);

	void lock(bool doLock);

	void lock(ManagedObject* obj);

	void rlock(bool doLock);

	void wlock(bool doLock);

	void wlock(ManagedObject* obj);

	void unlock(bool doLock);

	void runlock(bool doLock);

	void setLockName(const String& name);

	void writeObject(String& data);

	void readObject(const String& data);

protected:
	String _param0_setLockName__String_;
	String _param0_writeObject__String_;
	String _param0_readObject__String_;
};

class ManagedObjectHelper : public DistributedObjectClassHelper, public Singleton<ManagedObjectHelper> {
	static ManagedObjectHelper* staticInitializer;

public:
	ManagedObjectHelper();

	void finalizeHelper();

	DistributedObject* instantiateObject();

	DistributedObjectServant* instantiateServant();

	DistributedObjectAdapter* createAdapter(DistributedObjectStub* obj);

	friend class Singleton<ManagedObjectHelper>;
};

} // namespace core
} // namespace engine

using namespace engine::core;

#endif /*MANAGEDOBJECT_H_*/
