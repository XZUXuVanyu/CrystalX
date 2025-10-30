# **CrystalX::Event**

## Introduction  

CrystalX::Event is responsible for handling various types of events that might take place in CrystalX engine  

## Member  

**EventType**  
Declair all types of events in CrystalX  

``` C++
enum class EventType
{
    None = 0,
    EventType...
}
```  

---  

**Event**  
Base class for events  

``` C++
class CRYSTALX_API Event
{
public:
    virtual ~Event() = default;
    virtual EventType GetEventType() const = 0;
    bool m_EventHandled = false;
}
```  

**EventDispatcher**  
EventDispatcher will do automatic event typecheck in compile time, providing convenience for registering callbacks  

``` C++
class EventDispatcher
{
public:
    EventDispatcher(Event event) : m_Event(event) { CRYSTALX_trace("create"); };

    template<typename TypeToCheck, typename FunctionType>
    bool Dispatch(const FunctionType& callbackfunction);

private:
    Event& m_Event;
}
```  
