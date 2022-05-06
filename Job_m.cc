//
// Generated file, do not edit! Created by nedtool 5.6 from Job.msg.
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
#include "Job_m.h"

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
    for (int i=0; i<n; i++) {
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
    for (int i=0; i<n; i++) {
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
    for (int i=0; i<n; i++) {
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


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(Job)

Job::Job(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    this->cached = false;
    this->back_from_ost = false;
    this->work_type = 0;
    this->assigned_oss_id = 0;
    this->job_id = 0;
    this->init_data_size = 0;
    this->arrive_time_queue = 0;
    this->leave_time_queue = 0;
    this->arrive_time_server = 0;
    this->leave_time_server = 0;
    take(&(this->pkg));
}

Job::Job(const Job& other) : ::omnetpp::cMessage(other)
{
    take(&(this->pkg));
    copy(other);
}

Job::~Job()
{
    drop(&(this->pkg));
}

Job& Job::operator=(const Job& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void Job::copy(const Job& other)
{
    this->cached = other.cached;
    this->back_from_ost = other.back_from_ost;
    this->work_type = other.work_type;
    this->assigned_oss_id = other.assigned_oss_id;
    this->job_id = other.job_id;
    this->init_data_size = other.init_data_size;
    this->arrive_time_queue = other.arrive_time_queue;
    this->leave_time_queue = other.leave_time_queue;
    this->arrive_time_server = other.arrive_time_server;
    this->leave_time_server = other.leave_time_server;
    this->pkg = other.pkg;
    this->pkg.setName(other.pkg.getName());
}

void Job::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->cached);
    doParsimPacking(b,this->back_from_ost);
    doParsimPacking(b,this->work_type);
    doParsimPacking(b,this->assigned_oss_id);
    doParsimPacking(b,this->job_id);
    doParsimPacking(b,this->init_data_size);
    doParsimPacking(b,this->arrive_time_queue);
    doParsimPacking(b,this->leave_time_queue);
    doParsimPacking(b,this->arrive_time_server);
    doParsimPacking(b,this->leave_time_server);
    doParsimPacking(b,this->pkg);
}

void Job::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->cached);
    doParsimUnpacking(b,this->back_from_ost);
    doParsimUnpacking(b,this->work_type);
    doParsimUnpacking(b,this->assigned_oss_id);
    doParsimUnpacking(b,this->job_id);
    doParsimUnpacking(b,this->init_data_size);
    doParsimUnpacking(b,this->arrive_time_queue);
    doParsimUnpacking(b,this->leave_time_queue);
    doParsimUnpacking(b,this->arrive_time_server);
    doParsimUnpacking(b,this->leave_time_server);
    doParsimUnpacking(b,this->pkg);
}

bool Job::getCached() const
{
    return this->cached;
}

void Job::setCached(bool cached)
{
    this->cached = cached;
}

bool Job::getBack_from_ost() const
{
    return this->back_from_ost;
}

void Job::setBack_from_ost(bool back_from_ost)
{
    this->back_from_ost = back_from_ost;
}

char Job::getWork_type() const
{
    return this->work_type;
}

void Job::setWork_type(char work_type)
{
    this->work_type = work_type;
}

int Job::getAssigned_oss_id() const
{
    return this->assigned_oss_id;
}

void Job::setAssigned_oss_id(int assigned_oss_id)
{
    this->assigned_oss_id = assigned_oss_id;
}

unsigned int Job::getJob_id() const
{
    return this->job_id;
}

void Job::setJob_id(unsigned int job_id)
{
    this->job_id = job_id;
}

uint64_t Job::getInit_data_size() const
{
    return this->init_data_size;
}

void Job::setInit_data_size(uint64_t init_data_size)
{
    this->init_data_size = init_data_size;
}

::omnetpp::simtime_t Job::getArrive_time_queue() const
{
    return this->arrive_time_queue;
}

void Job::setArrive_time_queue(::omnetpp::simtime_t arrive_time_queue)
{
    this->arrive_time_queue = arrive_time_queue;
}

::omnetpp::simtime_t Job::getLeave_time_queue() const
{
    return this->leave_time_queue;
}

void Job::setLeave_time_queue(::omnetpp::simtime_t leave_time_queue)
{
    this->leave_time_queue = leave_time_queue;
}

::omnetpp::simtime_t Job::getArrive_time_server() const
{
    return this->arrive_time_server;
}

void Job::setArrive_time_server(::omnetpp::simtime_t arrive_time_server)
{
    this->arrive_time_server = arrive_time_server;
}

::omnetpp::simtime_t Job::getLeave_time_server() const
{
    return this->leave_time_server;
}

void Job::setLeave_time_server(::omnetpp::simtime_t leave_time_server)
{
    this->leave_time_server = leave_time_server;
}

omnetpp::cPacket& Job::getPkg()
{
    return this->pkg;
}

void Job::setPkg(const omnetpp::cPacket& pkg)
{
    this->pkg = pkg;
}

class JobDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    JobDescriptor();
    virtual ~JobDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(JobDescriptor)

JobDescriptor::JobDescriptor() : omnetpp::cClassDescriptor("Job", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

JobDescriptor::~JobDescriptor()
{
    delete[] propertynames;
}

bool JobDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<Job *>(obj)!=nullptr;
}

const char **JobDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *JobDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int JobDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 11+basedesc->getFieldCount() : 11;
}

unsigned int JobDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND | FD_ISCOBJECT | FD_ISCOWNEDOBJECT,
    };
    return (field>=0 && field<11) ? fieldTypeFlags[field] : 0;
}

const char *JobDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "cached",
        "back_from_ost",
        "work_type",
        "assigned_oss_id",
        "job_id",
        "init_data_size",
        "arrive_time_queue",
        "leave_time_queue",
        "arrive_time_server",
        "leave_time_server",
        "pkg",
    };
    return (field>=0 && field<11) ? fieldNames[field] : nullptr;
}

int JobDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "cached")==0) return base+0;
    if (fieldName[0]=='b' && strcmp(fieldName, "back_from_ost")==0) return base+1;
    if (fieldName[0]=='w' && strcmp(fieldName, "work_type")==0) return base+2;
    if (fieldName[0]=='a' && strcmp(fieldName, "assigned_oss_id")==0) return base+3;
    if (fieldName[0]=='j' && strcmp(fieldName, "job_id")==0) return base+4;
    if (fieldName[0]=='i' && strcmp(fieldName, "init_data_size")==0) return base+5;
    if (fieldName[0]=='a' && strcmp(fieldName, "arrive_time_queue")==0) return base+6;
    if (fieldName[0]=='l' && strcmp(fieldName, "leave_time_queue")==0) return base+7;
    if (fieldName[0]=='a' && strcmp(fieldName, "arrive_time_server")==0) return base+8;
    if (fieldName[0]=='l' && strcmp(fieldName, "leave_time_server")==0) return base+9;
    if (fieldName[0]=='p' && strcmp(fieldName, "pkg")==0) return base+10;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *JobDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",
        "bool",
        "char",
        "int",
        "unsigned int",
        "uint64_t",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "simtime_t",
        "omnetpp::cPacket",
    };
    return (field>=0 && field<11) ? fieldTypeStrings[field] : nullptr;
}

const char **JobDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *JobDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int JobDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    Job *pp = (Job *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *JobDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Job *pp = (Job *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string JobDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    Job *pp = (Job *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getCached());
        case 1: return bool2string(pp->getBack_from_ost());
        case 2: return long2string(pp->getWork_type());
        case 3: return long2string(pp->getAssigned_oss_id());
        case 4: return ulong2string(pp->getJob_id());
        case 5: return uint642string(pp->getInit_data_size());
        case 6: return simtime2string(pp->getArrive_time_queue());
        case 7: return simtime2string(pp->getLeave_time_queue());
        case 8: return simtime2string(pp->getArrive_time_server());
        case 9: return simtime2string(pp->getLeave_time_server());
        case 10: {std::stringstream out; out << pp->getPkg(); return out.str();}
        default: return "";
    }
}

bool JobDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    Job *pp = (Job *)object; (void)pp;
    switch (field) {
        case 0: pp->setCached(string2bool(value)); return true;
        case 1: pp->setBack_from_ost(string2bool(value)); return true;
        case 2: pp->setWork_type(string2long(value)); return true;
        case 3: pp->setAssigned_oss_id(string2long(value)); return true;
        case 4: pp->setJob_id(string2ulong(value)); return true;
        case 5: pp->setInit_data_size(string2uint64(value)); return true;
        case 6: pp->setArrive_time_queue(string2simtime(value)); return true;
        case 7: pp->setLeave_time_queue(string2simtime(value)); return true;
        case 8: pp->setArrive_time_server(string2simtime(value)); return true;
        case 9: pp->setLeave_time_server(string2simtime(value)); return true;
        default: return false;
    }
}

const char *JobDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 10: return omnetpp::opp_typename(typeid(omnetpp::cPacket));
        default: return nullptr;
    };
}

void *JobDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    Job *pp = (Job *)object; (void)pp;
    switch (field) {
        case 10: return (void *)static_cast<omnetpp::cObject *>(&pp->getPkg()); break;
        default: return nullptr;
    }
}


