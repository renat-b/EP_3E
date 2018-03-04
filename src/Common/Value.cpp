#include "StdAfx.h"
#include "Value.h"

Value::Value() : m_data(nullptr), m_element_size(0), m_dimension(0), m_size_column(0), m_size_row(0)
{

}

Value::Value(const Value &other) : m_data(nullptr), m_element_size(0), m_dimension(0), m_size_column(0), m_size_row(0)
{
    Assign(other);
}

Value::~Value()
{
    Shutdow();
}

bool Value::Create(uint32_t elememnt_size)
{
    if (m_dimension == 0 && elememnt_size == m_element_size)
    {
        return true;
    }

        
    Shutdow();

    m_element_size = elememnt_size;
    m_dimension    = 0;
    m_size_column  = 0;
    m_size_row     = 0;

    m_data = new(std::nothrow) uint8_t[m_element_size];
    if (!m_data)
        return false;

    memset(m_data, 0, m_element_size);
    return true;
}

bool Value::Create1d(uint32_t element_size, uint8_t size_column)
{
    if (m_dimension == 1 && element_size == m_element_size && size_column == m_size_column)
    {
        return true;
    }


    Shutdow();

    m_element_size = element_size;
    m_dimension    = 1;
    m_size_column  = size_column;
    m_size_row     = 0;
    
    uint32_t full_size = m_element_size * m_size_column;
    m_data = new(std::nothrow) uint8_t[full_size];
    if (!m_data)
        return false;

    memset(m_data, 0, full_size);
    return true;
}

bool Value::Create2d(uint32_t element_size, uint8_t size_column, uint8_t size_row)
{
    Shutdow();

    m_element_size = element_size;
    m_dimension    = 2;
    m_size_column  = size_column;
    m_size_row     = size_row;
    
    uint32_t full_size = m_element_size * m_size_column * m_size_row;
    m_data = new(std::nothrow) uint8_t[full_size];
    if (!m_data)
        return false;

    memset(m_data, 0, full_size);
    return true;;
}

bool Value::CreateByTemplate(const Value& template_value)
{
    bool check = (Dims() == template_value.Dims());
    if (check)
        check = (ElemSize() == template_value.ElemSize());
    if (check)
        if (1 == template_value.Dims())
            check = (Size(0) == template_value.Size(0));


    if (!check)
    {
        if (0 == template_value.Dims())
        {
            if (!Create(template_value.ElemSize()))
                return false;
        }
        else if (1 == template_value.Dims())
        {
            if (!Create1d(template_value.ElemSize(), template_value.Size(0)))
                return false;
        }
        else
            return false;
    }
    return true;
}

void Value::Shutdow()
{
    if (m_data)
        delete[] m_data;

    m_data = nullptr;
    m_dimension = 0;
    m_element_size = 0;
    m_size_column = 0;
    m_size_row = 0;
}

uint32_t Value::Dims() const
{
    return m_dimension;
}

uint32_t Value::Size(int dim) const
{
    if (1 == dim)
        return m_size_column; 
    else if (2 == dim)
        return m_size_row;

    return 0;
}

uint16_t Value::ElemSize() const
{
    return m_element_size;
}

bool Value::Assign(const Value &other)
{
    // free old data
    Shutdow();   

    // assign new values
    m_element_size = other.m_element_size;
    m_dimension    = other.m_dimension;
    m_size_column  = other.m_size_column;
    m_size_row     = other.m_size_row;
   
    // allocate new memory 
    uint32_t full_size = m_element_size; 
    if (1 == m_dimension)
        full_size = m_size_column * m_element_size;
    else if (2 == m_dimension)
        full_size = m_size_column * m_size_row * m_element_size;
       
    m_data = new(std::nothrow) uint8_t[full_size];
    if (!m_data)
        return false;
    
    if (memcpy(m_data, other.m_data, full_size) == nullptr)
        return false;
    return true;
}

bool Value::IsEmpty() const
{
    bool r = (m_data == nullptr);
    return r;
}

Value& Value::operator=(const Value &value)
{
    Assign(value);
    return (*this);
}

uint8_t* Value::Ptr()
{
    if (!m_data)
        return nullptr;

    if (m_dimension == 0)
        return m_data;

    return nullptr;
}

const uint8_t *Value::Ptr() const
{
    if (!m_data)
        return nullptr;

    if (m_dimension == 0)
        return m_data;

    return nullptr;
}

uint8_t *Value::Ptr(uint8_t column)
{
    if (!m_data)
        return nullptr;

    if (column >= m_size_column)
        return nullptr;

    if (m_dimension != 1)
        return nullptr;

    return m_data + column * m_element_size;
}

const uint8_t *Value::Ptr(uint8_t column) const
{
    if (!m_data)
        return nullptr;

    if (column >= m_size_column)
        return nullptr;

    if (m_dimension != 1)
        return nullptr;

    return m_data + column * m_element_size;
}

uint8_t *Value::Ptr(uint8_t column, uint8_t row)
{
    if (!m_data)
        return nullptr;

    if (m_dimension != 2)
        return nullptr;

    if (m_size_column >= column || m_size_row >= row)
        return nullptr;

    uint32_t row_size = m_element_size * m_size_column;

    uint8_t *ptr = m_data + (row * row_size) + (m_element_size * column);
    return ptr;
}

const uint8_t *Value::Ptr(uint8_t column, uint8_t row) const
{
    if (!m_data)
        return nullptr;

    if (m_dimension != 2)
        return nullptr;

    if (m_size_column >= column || m_size_row >= row)
        return nullptr;

    uint32_t row_size = m_element_size * m_size_column;

    uint8_t *ptr = m_data + (row * row_size) + (m_element_size * column);
    return ptr;
}
