#ifndef ITOOL_CLASSES_H
#define ITOOL_CLASSES_H

#include <tuple>
#include <vector>
#include <string>
#include <limits>

///Пространство имен IndigoSuite
namespace IndigoSuite {
    using namespace std;
    ///Набор возможных типов первого столбца калибровочной талбицы
    enum TypeFirstColumn
    {
        Text,   ///< Текстовый тип
        Numbers ///< Числовой тип
    };

    ///Набор возможных режимов работы библиотеки
    enum TypeWorkMode
    {
        Base,    ///< Режим работы, в котором часть функционала, которую разработчик считает расширеной, не показывается пользователю
        Advanced ///< Режим работы, в котором пользователю доступен весь функционал класса.
    };

    ///Набор возможных статусов прибора
    enum StatusCode
    {
        NA,       ///< Прибор недоступен
        Ready,    ///< Прибор готов к работе
        Work,     ///< Прибор работает в автономном режиме
        Idle,     ///< Прибор остановлен
        EwlWork,  ///< Прибор работает в кабельном режиме
        EwlPause  ///< Прибор приостановлен. Возможно возобновление работы прибора в кабельном режиме
    };

    ///Набор возможных кодов валидности циклограммы
    enum CycloValidateCode
    {
        Ok,                 ///< Циклограмма валидна
        TooLong,            ///< Слишком длинная по времени циклограмма. Данные не поместятся в память
        TooManyIntervals,   ///< Слишком много интервалов
        MemoryCheckFail,    ///< Не удалось проверить память
        MemoryClearFail,    ///< Не удалось стереть память
        Invalid             ///< Другая причина
    };

    ///Набор возможных типов соединения с прибором
    enum ConnectionType
    {
        USB, ///< USB соединение. При выборе данного типа библиотека сама открывает, настраивает и закрывает порт.
        SP   ///< ComPort соединение. При выборе данного типа за открытие, настройку и закрытие порта ответсвенен верхний софт.
    };

    ///Набор возможных типов сообщения
    namespace IndigoMessage
    {
        enum MessageType
        {
            LogFileOnly = -1,    ///< log file only
            Ok = 0,                ///< green
            Error = 1,            ///< red
            Warning = 2            ///< yellow
        };
    }

    ///Набор возможных способов обработки данных при нарезке
    enum ProcessingTypeCode
    {
        Unkown = -1,
        LinearSpline = 0,
        AkimaSpline = 1,
        CubicSpline = 2,
        Average = 3,
        Median = 4
    };

    ///Тип лога
    enum LogType
    {
        TypicalType = 0, ///< Лог не являющий ни логом глубины ни логом времен
        DepthType = 1,   ///< Лог глубины
        TimeLog = 2      ///< Лог времени
    };

    //!Текущая версия ITool
    const std::string ITOOL_VERSION = "4.6.0";

    //!Функция для неиспользуемых параметров
    template<class... T> void unused(T&&...){ }


    /// Псевдоним для типа ID, чтобы легко менять его тип
    using ToolID = int;

    /*!
        Класс, позволяющий группировать параметры датчиков
        прибора по некоторым признакам. Группа характеризуется
        своим идентификатором целого типа.
        */
    //!Группа
    class Group
    {
        int _group;///< Индетификатор группы

    public:
        //!Конструктор
        Group() : Group(0) {}

        //!Конструктор принмающий индетификатор группы
        Group(int group)
            : _group(group) {}

        virtual ~Group() = default;

        int group() const { return _group; }

        void set_group(int group) { _group = group; }
    };


    /*!
        Класс, реализующий параметр прибора
        численного типа. Например частота замера датчика.
        */
    //!Параметр численного типа
    class NumbersObjectInfo : public  Group
    {
        std::string _name;
        std::string _unit;
        double _min_value;
        double _max_value;
        double _step;
        double _default_value;

    public:

        NumbersObjectInfo(
            const std::string& name = "",
            const std::string& unit = "",
            double min_value = 0.0,
            double max_value = 100000.0,
            double step = 0.5,
            double default_value = 0.0,
            int group = 0) :
            Group(group),
            _name(name),
            _unit(unit),
            _min_value(min_value),
            _max_value(max_value),
            _step(step),
            _default_value(default_value)
        {}

        std::string name() const { return _name; }
        void set_name(const std::string& name) { _name = name; }

        std::string unit() const { return _unit; }
        void set_unit(const std::string& unit) { _unit = unit; }

        double min_value() const { return _min_value; }
        void set_min_value(double value) { _min_value = value; }

        double max_value() const { return _max_value; }
        void set_max_value(double value) { _max_value = value; }

        double step() const { return _step; }
        void set_step(double value) { _step = value; }

        double default_value() const { return _default_value; }
        void set_default_value(double value) { _default_value = value; }
    };

    /*!
        Класс, реализующий параметр прибора логического
        типа. Например, датчик может быть включен или выключен.
        */
    //! Параметр логического типа
    class StateObjectInfo : public Group
    {
        std::string _name;
        std::string _unit;
        bool _default_state;

    public:
        StateObjectInfo(
            const std::string& name = "",
            const std::string& unit = "",
            bool default_state = true,
            int group = 0) :
            Group(group),
            _name(name),
            _unit(unit),
            _default_state(default_state)
        {}

        std::string name() const { return _name; }
        void set_name(const std::string& name) { _name = name; }

        std::string unit() const { return _unit; }
        void set_unit(const std::string& unit) { _unit = unit; }

        bool default_state() const { return _default_state; }
        void set_default_state(bool default_state) { _default_state = default_state; }
    };

    /*!
        Класс, реализующий параметр прибора с
        возможностью выбора значения из выпадающего списка.
        */
    //! Параметр в виде списка
    class ListObjectInfo : public Group
    {
        std::string _name;
        std::string _unit;
        std::vector<std::string> _data;
        int _default_index;
        bool _is_custom_item;
        NumbersObjectInfo _number;

    public:

        ListObjectInfo(
            const std::string& name = "",
            const std::string& unit = "",
            int default_index = 0,
            bool is_custom_item = false,
            int group = 0) :
            Group(group),
            _name(name),
            _unit(unit),
            _data(std::vector<std::string>()),
            _default_index(default_index),
            _is_custom_item(is_custom_item),
            _number(NumbersObjectInfo())
        {}


        ListObjectInfo(const std::vector<std::string>& data)
            : ListObjectInfo()
        {
            _data = data;
        }

        std::string name() const { return _name; }
        void set_name(const std::string& name) { _name = name; }

        std::string unit() const { return _unit; }
        void set_unit(const std::string& unit) { _unit = unit; }

        size_t size() const { return _data.size(); }

        std::string item(size_t index) const
        {
            std::string res = "";
            if (index < _data.size())
                res = _data[index];
            return res;
        }

        void set_data(const std::vector<std::string>& data) { _data = data; }
        std::vector<std::string> data() const { return _data; }


        bool is_custom() const { return _is_custom_item; }
        void set_custom_mode(bool f) { _is_custom_item = f; }

        NumbersObjectInfo number_info() const { return _number; }
        void set_number_info(const NumbersObjectInfo& info) { _number = info; }

        int default_index() const { return _default_index; }
        void set_default_index(int default_index) { _default_index = default_index; }
    };

    /*!
        Класс, реализующий объединение нескольких
        параметров. Чаще всего такое объединение представляет собой сенсор
        Например, сенсор может быть включен или выключен, также он должен иметь
        частоту записи данных. Таким образом этот сенсор объединяет в себе два
        параметра: логического и численного типа.
        */
    //! Объединение параметров (Сенсор)
    class ParameterInfo
    {
        std::string _name;

        NumbersObjectInfo _number;
        StateObjectInfo _state;
        ListObjectInfo _lst;

        bool _is_number;
        bool _is_state;
        bool _is_lst;

        bool _single_mode;

        void reset() { _is_number = _is_state = _is_lst = false; }

    public:
        ParameterInfo()
        {
            reset();
            _single_mode = false;
        }

        std::string name() const { return _name; }

        void set_name(const std::string& name) { _name = name; }

        bool is_single_mode() const { return _single_mode; }

        void set_single_mode(bool f)
        {
            _single_mode = f;
            if (_single_mode)
                reset();
        }

        //
        StateObjectInfo state() const { return _state; }

        void set_state(const StateObjectInfo& state)
        {
            set_state_active(true);
            _state = state;
        }
        //

        //
        NumbersObjectInfo number() const { return _number; }

        void set_number(const NumbersObjectInfo& number)
        {
            set_number_active(true);
            _number = number;
        }
        //

        //
        ListObjectInfo lst() const { return _lst; }

        void set_lst(const ListObjectInfo& lst)
        {
            set_lst_active(true);
            _lst = lst;
        }
        //

        bool is_number() const { return _is_number; }

        void set_number_active(bool is_number)
        {
            if (_single_mode && is_number)
                reset();
            _is_number = is_number;
        }

        bool is_state() const { return _is_state; }

        void set_state_active(bool is_state)
        {
            if (_single_mode && is_state)
                reset();
            _is_state = is_state;
        }

        bool is_lst() const { return _is_lst; }

        void set_lst_active(bool is_lst)
        {
            if (_single_mode && is_lst)
                reset();
            _is_lst = is_lst;
        }
    };


    //! Идентификатор лога
    struct LogId
    {
        int _id;    ///< id лога
        int _group; ///< id группы лога;

        LogId() { _id = _group = 0; }
    };


    //! Служебная информация лога
    struct LogHeader
    {
        std::string _name;
        std::string _description;
        std::string _unit;
        bool _visible = true;
        LogId _id;
        int _sensorId;
        ProcessingTypeCode _type = LinearSpline;
        bool _exportable = true;
        LogType _logtype = TypicalType;
        unsigned short operation = 0;
        double axis = 0.0;
    };

    //! Сенсор
    class Sensor
    {
        std::string _name; ///< Имя сенсора
        int _id;      ///< Индетификатор сенсора

    public:

        ///Конструктор
        Sensor(const std::string& name = "", int id = -1) :
            _name(name), _id(id) {}

        std::string name() const { return _name; }
        void setName(const std::string& val) { _name = val; }

        int id() const { return _id; }
        void setId(int id) { _id = id; }
    };

    /*!
        Класс, реализующий калибровочную таблицу.
        Таблица произвольного размера, которая может хранить калибровку двух типов:
        Табличную и калибровочные коэффициенты.
        */
    //! Калибровочная таблица
    class CalibrationTable
    {
    protected:
        TypeFirstColumn _type;                      //Тип первого солбца
        std::string _name;

        ToolID _tool_id;
        int _id;
        std::string _serial_n;

        bool      _has_horizontal_header;                      //Наличие горизонтальной шапки
        std::vector<std::string> _header;                     //Горизонтальная шапка с учетом первого сnолбца (_w + 1 )
        std::vector<std::string> _names;                      //Имена. Будут отображаться в первом столбце, если type = Text
        std::vector<double>      _values;                      //Числа в первом столбце, если type = Numbers
        std::vector<std::vector<double> > _coefficients;      //калибровочные коэффициенты

        void default_init()
        {
            _has_horizontal_header = false;
            _id = 0;
            _tool_id = 0;
        }

    public:
        CalibrationTable(TypeFirstColumn type = TypeFirstColumn::Numbers)
            : _type(type)
        {
            default_init();
        }

        CalibrationTable(const std::string& name, const std::vector<std::vector<double>>& coef, TypeFirstColumn type = TypeFirstColumn::Numbers)
            : _type(type), _name(name)
        {
            default_init();
            set_coefficients(coef);
        }

        void set_id(int id) { _id = id; }

        int id() const { return _id; }

        void set_tool_id(ToolID id) { _tool_id = id; }

        ToolID tool_id() const { return _tool_id; }

        void set_serial_n(const std::string& serial_n) { _serial_n = serial_n; }

        std::string serial_n() const { return _serial_n; }

        size_t width() const
        {
            if (!_coefficients.empty())
                return _coefficients[0].size();
            return 0;
        }

        size_t height() const { return _coefficients.size(); }

        std::string get_name() const { return _name; }

        void set_name(const std::string& name) { _name = name; }

        TypeFirstColumn type() const { return _type; }

        std::vector<std::vector<double> > get_coefficients() const { return _coefficients; }

        void set_coefficients(const std::vector<std::vector<double> >& coeff) { _coefficients = coeff; }

        double get_coef(int i, int j) const { return _coefficients.at(i).at(j); }

        void set_coef(int i, int j, double val){ _coefficients[i][j] = val; }

        double value(int i) const { return _values.at(i); }

        void set_value(int i, double val) { _values[i] = val; }

        std::vector<std::string> get_names() const { return _names; }

        void set_names(const std::vector<std::string>& names)
        {
            _names = names;
            _type = TypeFirstColumn::Text;
            _values.clear();
        }

        std::vector<double> get_values() const { return _values; }

        void set_values(const std::vector<double>& values) {
            _values = values;
            _type = TypeFirstColumn::Numbers;
            _names.clear();
        }

        std::vector<std::string> get_header() const { return _header; }

        void set_header(const std::vector<std::string>& header) {
            _header = header;
            _has_horizontal_header = true;
        }

        bool has_horizontal_header() const { return _has_horizontal_header; }

        bool is_number_first_column() const { return _type == TypeFirstColumn::Numbers; }
    };

    //! Хранит информацию о приборе.
    struct ToolInfo
    {
        std::string    name;
        std::string    shortName;
        std::string    version;
        std::string    serialN;
        std::string    type;
        std::string    metaInfo;   // Мета информация которая будет записана в эскпортируемый файл
    };

    /*!
        Класс реализующий набор настроек. Внутри интервала хранятся некоторые значения
        параметров.
    */
    //!Набор настроек
    class Interval
    {
    protected:
        std::vector<std::tuple<bool, double, int> > _parameter_values; //(true-включен, false-выключен), количество секунд между измерениями

    public:
        virtual ~Interval() = default;

        void set_parameters(const std::vector<std::tuple<bool, double, int>>& sensors)
        {
            _parameter_values = sensors;
        }

        std::vector<std::tuple<bool, double, int>> get_parameters() const { return _parameter_values; }

        size_t count_parameters() const { return _parameter_values.size(); }

        std::tuple<bool, double, int> get_item(size_t index) const
        {
            if (index < _parameter_values.size())
                return _parameter_values[index];
            return std::make_tuple(false, 0.0, -1);
        }
    };

    /*!
        Класс, реализующий интервал циклограммы.
        Хранит набор настроек и длительность, в течение которой
        эти настройки активны
        */
    //!Интервал циклограммы
    class CycloInterval : public Interval
    {
        unsigned long long _duration;   //длительность общего интервала в секундах

    public:

        CycloInterval(unsigned long long duration = 0)
            : Interval(),
            _duration(duration)
        {}

        unsigned long long get_duration() const { return _duration; }
        void set_duration(unsigned long long duration) { _duration = duration; }
    };
    ///Тестируемый парметр
    struct TestParameter
    {
        std::string _name;              ///< Имя параметра
        std::string _unit;              ///< Единица измерения тестируемого параметра
        double      _value;             ///< Измеренное значение
        bool        _acceptable;        ///< Является ли значение параметра приемлемым
        bool        _obtained;          ///< Удалось ли получить значение параметра
        double      _leftBorderValue;    ///< левая граница коридора валидных значений
        double      _rightBorderValue;    ///< правая граница коридора валидных значений

        ///Конструктор
        TestParameter(const std::string& name = "", const std::string& unit = "") : 
            _name(name), _unit(unit), _value(0.0), _acceptable(false), _obtained(false),
            _leftBorderValue(-1 * (std::numeric_limits<double>::max)()),
            _rightBorderValue((std::numeric_limits<double>::max)())
        {}
    };
}


#endif // ITOOL_CLASSES_H


