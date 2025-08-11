//
// Generated file, do not edit! Created by opp_msgtool 6.1 from DVMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "DVMessage_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

RoutingEntry::RoutingEntry()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const RoutingEntry& a)
{
    doParsimPacking(b,a.destinationNode);
    doParsimPacking(b,a.cost);
}

void __doUnpacking(omnetpp::cCommBuffer *b, RoutingEntry& a)
{
    doParsimUnpacking(b,a.destinationNode);
    doParsimUnpacking(b,a.cost);
}

class RoutingEntryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_destinationNode,
        FIELD_cost,
    };
  public:
    RoutingEntryDescriptor();
    virtual ~RoutingEntryDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(RoutingEntryDescriptor)

RoutingEntryDescriptor::RoutingEntryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(RoutingEntry)), "")
{
    propertyNames = nullptr;
}

RoutingEntryDescriptor::~RoutingEntryDescriptor()
{
    delete[] propertyNames;
}

bool RoutingEntryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RoutingEntry *>(obj)!=nullptr;
}

const char **RoutingEntryDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RoutingEntryDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RoutingEntryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int RoutingEntryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_destinationNode
        FD_ISEDITABLE,    // FIELD_cost
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *RoutingEntryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "destinationNode",
        "cost",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int RoutingEntryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "destinationNode") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "cost") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *RoutingEntryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_destinationNode
        "double",    // FIELD_cost
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **RoutingEntryDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *RoutingEntryDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int RoutingEntryDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RoutingEntry *pp = omnetpp::fromAnyPtr<RoutingEntry>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RoutingEntryDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RoutingEntry *pp = omnetpp::fromAnyPtr<RoutingEntry>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RoutingEntry'", field);
    }
}

const char *RoutingEntryDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RoutingEntry *pp = omnetpp::fromAnyPtr<RoutingEntry>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RoutingEntryDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RoutingEntry *pp = omnetpp::fromAnyPtr<RoutingEntry>(object); (void)pp;
    switch (field) {
        case FIELD_destinationNode: return long2string(pp->destinationNode);
        case FIELD_cost: return double2string(pp->cost);
        default: return "";
    }
}

void RoutingEntryDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RoutingEntry *pp = omnetpp::fromAnyPtr<RoutingEntry>(object); (void)pp;
    switch (field) {
        case FIELD_destinationNode: pp->destinationNode = string2long(value); break;
        case FIELD_cost: pp->cost = string2double(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RoutingEntry'", field);
    }
}

omnetpp::cValue RoutingEntryDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RoutingEntry *pp = omnetpp::fromAnyPtr<RoutingEntry>(object); (void)pp;
    switch (field) {
        case FIELD_destinationNode: return pp->destinationNode;
        case FIELD_cost: return pp->cost;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RoutingEntry' as cValue -- field index out of range?", field);
    }
}

void RoutingEntryDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RoutingEntry *pp = omnetpp::fromAnyPtr<RoutingEntry>(object); (void)pp;
    switch (field) {
        case FIELD_destinationNode: pp->destinationNode = omnetpp::checked_int_cast<int>(value.intValue()); break;
        case FIELD_cost: pp->cost = value.doubleValue(); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RoutingEntry'", field);
    }
}

const char *RoutingEntryDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr RoutingEntryDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RoutingEntry *pp = omnetpp::fromAnyPtr<RoutingEntry>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RoutingEntryDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RoutingEntry *pp = omnetpp::fromAnyPtr<RoutingEntry>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RoutingEntry'", field);
    }
}

Register_Class(DVMessage)

DVMessage::DVMessage(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

DVMessage::DVMessage(const DVMessage& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

DVMessage::~DVMessage()
{
    delete [] this->distanceVector;
}

DVMessage& DVMessage::operator=(const DVMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void DVMessage::copy(const DVMessage& other)
{
    delete [] this->distanceVector;
    this->distanceVector = (other.distanceVector_arraysize==0) ? nullptr : new RoutingEntry[other.distanceVector_arraysize];
    distanceVector_arraysize = other.distanceVector_arraysize;
    for (size_t i = 0; i < distanceVector_arraysize; i++) {
        this->distanceVector[i] = other.distanceVector[i];
    }
}

void DVMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    b->pack(distanceVector_arraysize);
    doParsimArrayPacking(b,this->distanceVector,distanceVector_arraysize);
}

void DVMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    delete [] this->distanceVector;
    b->unpack(distanceVector_arraysize);
    if (distanceVector_arraysize == 0) {
        this->distanceVector = nullptr;
    } else {
        this->distanceVector = new RoutingEntry[distanceVector_arraysize];
        doParsimArrayUnpacking(b,this->distanceVector,distanceVector_arraysize);
    }
}

size_t DVMessage::getDistanceVectorArraySize() const
{
    return distanceVector_arraysize;
}

const RoutingEntry& DVMessage::getDistanceVector(size_t k) const
{
    if (k >= distanceVector_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)distanceVector_arraysize, (unsigned long)k);
    return this->distanceVector[k];
}

void DVMessage::setDistanceVectorArraySize(size_t newSize)
{
    RoutingEntry *distanceVector2 = (newSize==0) ? nullptr : new RoutingEntry[newSize];
    size_t minSize = distanceVector_arraysize < newSize ? distanceVector_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        distanceVector2[i] = this->distanceVector[i];
    delete [] this->distanceVector;
    this->distanceVector = distanceVector2;
    distanceVector_arraysize = newSize;
}

void DVMessage::setDistanceVector(size_t k, const RoutingEntry& distanceVector)
{
    if (k >= distanceVector_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)distanceVector_arraysize, (unsigned long)k);
    this->distanceVector[k] = distanceVector;
}

void DVMessage::insertDistanceVector(size_t k, const RoutingEntry& distanceVector)
{
    if (k > distanceVector_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)distanceVector_arraysize, (unsigned long)k);
    size_t newSize = distanceVector_arraysize + 1;
    RoutingEntry *distanceVector2 = new RoutingEntry[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        distanceVector2[i] = this->distanceVector[i];
    distanceVector2[k] = distanceVector;
    for (i = k + 1; i < newSize; i++)
        distanceVector2[i] = this->distanceVector[i-1];
    delete [] this->distanceVector;
    this->distanceVector = distanceVector2;
    distanceVector_arraysize = newSize;
}

void DVMessage::appendDistanceVector(const RoutingEntry& distanceVector)
{
    insertDistanceVector(distanceVector_arraysize, distanceVector);
}

void DVMessage::eraseDistanceVector(size_t k)
{
    if (k >= distanceVector_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)distanceVector_arraysize, (unsigned long)k);
    size_t newSize = distanceVector_arraysize - 1;
    RoutingEntry *distanceVector2 = (newSize == 0) ? nullptr : new RoutingEntry[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        distanceVector2[i] = this->distanceVector[i];
    for (i = k; i < newSize; i++)
        distanceVector2[i] = this->distanceVector[i+1];
    delete [] this->distanceVector;
    this->distanceVector = distanceVector2;
    distanceVector_arraysize = newSize;
}

class DVMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_distanceVector,
    };
  public:
    DVMessageDescriptor();
    virtual ~DVMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(DVMessageDescriptor)

DVMessageDescriptor::DVMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(DVMessage)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

DVMessageDescriptor::~DVMessageDescriptor()
{
    delete[] propertyNames;
}

bool DVMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DVMessage *>(obj)!=nullptr;
}

const char **DVMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *DVMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int DVMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int DVMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_distanceVector
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *DVMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "distanceVector",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int DVMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "distanceVector") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *DVMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "RoutingEntry",    // FIELD_distanceVector
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **DVMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *DVMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int DVMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    DVMessage *pp = omnetpp::fromAnyPtr<DVMessage>(object); (void)pp;
    switch (field) {
        case FIELD_distanceVector: return pp->getDistanceVectorArraySize();
        default: return 0;
    }
}

void DVMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    DVMessage *pp = omnetpp::fromAnyPtr<DVMessage>(object); (void)pp;
    switch (field) {
        case FIELD_distanceVector: pp->setDistanceVectorArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'DVMessage'", field);
    }
}

const char *DVMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    DVMessage *pp = omnetpp::fromAnyPtr<DVMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DVMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    DVMessage *pp = omnetpp::fromAnyPtr<DVMessage>(object); (void)pp;
    switch (field) {
        case FIELD_distanceVector: return "";
        default: return "";
    }
}

void DVMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DVMessage *pp = omnetpp::fromAnyPtr<DVMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DVMessage'", field);
    }
}

omnetpp::cValue DVMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    DVMessage *pp = omnetpp::fromAnyPtr<DVMessage>(object); (void)pp;
    switch (field) {
        case FIELD_distanceVector: return omnetpp::toAnyPtr(&pp->getDistanceVector(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'DVMessage' as cValue -- field index out of range?", field);
    }
}

void DVMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DVMessage *pp = omnetpp::fromAnyPtr<DVMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DVMessage'", field);
    }
}

const char *DVMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_distanceVector: return omnetpp::opp_typename(typeid(RoutingEntry));
        default: return nullptr;
    };
}

omnetpp::any_ptr DVMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    DVMessage *pp = omnetpp::fromAnyPtr<DVMessage>(object); (void)pp;
    switch (field) {
        case FIELD_distanceVector: return omnetpp::toAnyPtr(&pp->getDistanceVector(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void DVMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    DVMessage *pp = omnetpp::fromAnyPtr<DVMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DVMessage'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

