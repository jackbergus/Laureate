#include <iostream>
#include <string>
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp> // Boost.Python

int main(int argc, char* argv[])
{
    Py_Initialize(); // ��ʼ�� Python ������

    try
    {
        // ���ģ���������·����Python�ű��ļ���·����
        boost::python::import("sys").attr("path").attr("append")(".");

        // 1. ����ģ�� hello��hello.py��
        boost::python::object hello = boost::python::import("hello");

        // 2. ��ȡ���ԣ���������ȣ�
        boost::python::object greeting = hello.attr("greeting");

        // 3. ִ��Python����
        boost::python::object res = greeting("2022.04.23");
        // ���е�2���͵�3�����Ժϲ�Ϊ
        // boost::python::object res = hello.attr("greeting")("2022.04.23");

        // 4. ��ӡ���ؽ����ʹ�� boost::python::extract ת����
        std::string tmp = boost::python::extract<std::string>(res);
        std::cout << tmp << " ... C++" << std::endl;
    }
    catch (const boost::python::error_already_set&)
    {
        PyErr_Print();
        return 1;
    }

    Py_Finalize(); // ��ֹ Python ������
    return 0;
}
