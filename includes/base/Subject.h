#ifndef __ABSSUBJECT_H__
#define __ABSSUBJECT_H__

#include "Observer.h"
#include <memory>
#include <algorithm>
#include <vector>

namespace KQEvent {
    class Subject : public std::enable_shared_from_this<Subject> {
    public:
        using ObserverList_t =  std::vector<Observer::ObserverWeakPtr>;
        struct EventType {
            bool READ = false;
            bool WRITE = false;
            bool EXCEPT = false;
        };

        Subject(Subject const &) = delete;

        Subject const &operator=(Subject const &) = delete;

        using SubjectPtr = std::shared_ptr<Subject>;
        using SubjectWeakPtr = std::weak_ptr<Subject>;

        template<class ..._Arg>
        static SubjectPtr newInstance(_Arg ...args) {
            auto aNew = new Subject(std::forward<_Arg>(args)...);
            return SubjectPtr(aNew);
        }

        SubjectPtr getPtr(void) {
            return shared_from_this();
        }

        virtual void notifyReadObserver();

        virtual void notifyWriteObserver();

        virtual void notifyExceptObserver();

        void attachReadObserver(Observer::ObserverWeakPtr observer);

        void attachWriteObserver(Observer::ObserverWeakPtr observer);

        void attachExceptObserver(Observer::ObserverWeakPtr observer);

        void detachReadObserver(Observer::ObserverWeakPtr observer);

        void detachWriteObserver(Observer::ObserverWeakPtr observer);

        void detachExceptObserver(Observer::ObserverWeakPtr observer);

        struct EventType getEventMask() {
            return _eventMask;
        }

        void setReadEvent(bool on) {
            _eventMask.READ = on;
        }

        void setWriteEvent(bool on) {
            _eventMask.WRITE = on;
        }

        void setExceptEvent(bool on) {
            _eventMask.EXCEPT = on;
        }

        int getFd() { return _fd; }

        void setFd(int fd) { _fd = fd; }

    private:
        explicit Subject(int fd);

        ObserverList_t _readObserver;
        ObserverList_t _writeObserver;
        ObserverList_t _exceptObserver;
        EventType _eventMask;
        int _fd;
    };
}
#endif
