#pragma once

class Value
{
private:
        

private:
    uint8_t  *m_data;    
    uint32_t  m_element_size;

    uint8_t   m_dimension;
    uint8_t   m_size_column;
    uint8_t   m_size_row;


public:
    Value();
    Value(const Value &other);
    ~Value();
    
    bool      Create(uint32_t elememnt_size);
    bool      Create1d(uint32_t element_size, uint8_t size_column);
    bool      Create2d(uint32_t element_size, uint8_t size_column, uint8_t size_row);
    bool      CreateByTemplate(const Value& template_value);
    void      Shutdow();

    uint32_t  Dims() const;
    uint32_t  Size(int dim) const;
    uint16_t  ElemSize() const;

    bool      IsEmpty() const;
 
    bool      Assign(const Value &other);
    template<typename T>
    bool      Assign(const T& val, uint32_t column);

    Value&    operator = (const Value &value);
    template <typename T>
    void operator = (const T& value);

    template <typename T>
    operator T() const;

    template <typename T>
    void CopyTo(T &val) const;

    template<typename T>
    void CopyTo(T &val, uint32_t column) const;

    template<typename T>
    void CopyTo(T &val, uint32_t column, uint32_t row) const;
   
    uint8_t  *Ptr();
    const uint8_t  *Ptr() const;

    uint8_t  *Ptr(uint8_t i0);
    const uint8_t  *Ptr(uint8_t i0) const;

    uint8_t  *Ptr(uint8_t i0, uint8_t i1);
    const uint8_t  *Ptr(uint8_t i0, uint8_t i1) const;
};


template <typename T>
void Value::operator=(const T& value)
{
    if (sizeof(value) != m_element_size)
        return;

    memcpy(m_data, &value, sizeof(T));
}

template <typename T>
Value::operator T() const
{
    return *(T*)m_data;
}

template <typename T>
void Value::CopyTo(T &val) const
{
    val = *(T*)m_data;
}

template<typename T>
void Value::CopyTo(T &val, uint32_t column) const
{
    const uint8_t *ptr = Ptr(column);
    if (!ptr)
        return;
    
    val = *(T*)ptr;
}

template<typename T>
void Value::CopyTo(T &val, uint32_t column, uint32_t row) const
{
    const uint8_t *ptr = Ptr(column, row);
    if (!ptr)
        return;

    val = *(T*)ptr;
}

template<typename T>
bool Value::Assign(const T& val, uint32_t column)
{
    uint8_t *ptr = Ptr(column);
    if (!ptr)
        return false;
    
    if (!memcpy(ptr, &val, sizeof(val)))
        return false;

    return true;
}
