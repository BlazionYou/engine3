/*
 *	engine/core/ManagedObject.h generated by engine3 IDL compiler 0.60
 */

#ifndef MANAGEDOBJECT_H_
#define MANAGEDOBJECT_H_

#include "engine/core/Core.h"

#include "engine/core/ManagedReference.h"

#include "engine/core/ManagedWeakReference.h"

namespace engine {
namespace core {

class ObjectUpdateToDatabaseTask;

} // namespace core
} // namespace engine

using namespace engine::core;

#include "system/lang/Object.h"

#include "system/thread/ReadWriteLock.h"

#include "system/thread/Lockable.h"

#include "system/io/Serializable.h"

#include "system/io/ObjectInputStream.h"

#include "system/io/ObjectOutputStream.h"

#include "engine/orb/object/DistributedObjectServant.h"

namespace engine {
namespace core {

class ManagedObject : public DistributedObjectStub, public TransactionalObjectHeader<class ManagedObjectImplementation*> {
public:
	ManagedObject();

	void updateForWrite();

	void lock(bool doLock = true);

	void lock(ManagedObject* obj);

	void rlock(bool doLock = true);

	void wlock(bool doLock = true);

	void wlock(ManagedObject* obj);

	void unlock(bool doLock = true);

	void runlock(bool doLock = true);

	void setLockName(const String& name);

	bool notifyDestroy();

	void writeObject(ObjectOutputStream* stream);

	void readObject(ObjectInputStream* stream);

	bool toBinaryStream(ObjectOutputStream* stream);

	bool parseFromBinaryStream(ObjectInputStream* stream);

	void initializeTransientMembers();

	void updateToDatabase();

	void queueUpdateToDatabaseTask();

	void clearUpdateToDatabaseTask();

	unsigned int getLastCRCSave();

	void setLastCRCSave(unsigned int crc);

	bool isPersistent();

	int getPersistenceLevel();

	void setPersistent(int level);

	DistributedObjectServant* _getImplementation();

	void _setImplementation(DistributedObjectServant* servant);

protected:
	ManagedObject(DummyConstructorParameter* param);

	virtual ~ManagedObject();

	void _updateForWrite();

	void _lock(bool doLock = true);

	void _lock(ManagedObject* obj);

	void _rlock(bool doLock = true);

	void _wlock(bool doLock = true);

	void _wlock(ManagedObject* obj);

	void _unlock(bool doLock = true);

	void _runlock(bool doLock = true);

	void _setLockName(const String& name);

	bool _notifyDestroy();

	friend class ManagedObjectHelper;
};

class ManagedObjectImplementation : public DistributedObjectServant {
protected:
	int persistenceLevel;

private:
	unsigned int lastCRCSave;

protected:
	ObjectUpdateToDatabaseTask* updateToDatabaseTask;

	String _className;

public:
	ManagedObjectImplementation();
	ManagedObjectImplementation(DummyConstructorParameter* param);

	void updateForWrite();

	void lock(bool doLock = true);

	void lock(ManagedObject* obj);

	void rlock(bool doLock = true);

	void wlock(bool doLock = true);

	void wlock(ManagedObject* obj);

	void unlock(bool doLock = true);

	void runlock(bool doLock = true);

	void setLockName(const String& name);

	bool notifyDestroy();

	bool toBinaryStream(ObjectOutputStream* stream);

	bool parseFromBinaryStream(ObjectInputStream* stream);

	virtual void initializeTransientMembers();

	void updateToDatabase();

	virtual void queueUpdateToDatabaseTask();

	void clearUpdateToDatabaseTask();

	unsigned int getLastCRCSave();

	void setLastCRCSave(unsigned int crc);

	bool isPersistent();

	int getPersistenceLevel();

protected:
	void _setClassName(const String& name);

public:
	void setPersistent(int level);

	ManagedObject* _this;

	operator const ManagedObject*();

	DistributedObjectStub* _getStub();
	virtual void readObject(ObjectInputStream* stream);
	virtual void writeObject(ObjectOutputStream* stream);
protected:
	virtual ~ManagedObjectImplementation();

	Object* clone();

	void finalize();

	void _initializeImplementation();

	void _setStub(DistributedObjectStub* stub);

	void _serializationHelperMethod();
	bool readObjectMember(ObjectInputStream* stream, const String& name);
	int writeObjectMembers(ObjectOutputStream* stream);

	friend class ManagedObject;
	friend class TransactionalObjectHandle<ManagedObjectImplementation*>;
};

class ManagedObjectAdapter : public DistributedObjectAdapter {
public:
	ManagedObjectAdapter(ManagedObjectImplementation* impl);

	Packet* invokeMethod(sys::uint32 methid, DistributedMethod* method);

	void updateForWrite();

	void lock(bool doLock);

	void lock(ManagedObject* obj);

	void rlock(bool doLock);

	void wlock(bool doLock);

	void wlock(ManagedObject* obj);

	void unlock(bool doLock);

	void runlock(bool doLock);

	void setLockName(const String& name);

	bool notifyDestroy();

	void initializeTransientMembers();

	void updateToDatabase();

	void queueUpdateToDatabaseTask();

	void clearUpdateToDatabaseTask();

	unsigned int getLastCRCSave();

	void setLastCRCSave(unsigned int crc);

protected:
	String _param0_setLockName__String_;
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
