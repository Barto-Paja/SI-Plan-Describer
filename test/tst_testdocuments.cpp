#include <QtTest>

#include "../Plan-Describer/document.hpp"
// add necessary includes here

class testDocuments : public QObject
{
    Q_OBJECT

public:
    testDocuments();
    ~testDocuments();

private slots:
    void test_case1();

};

testDocuments::testDocuments()
{

}

testDocuments::~testDocuments()
{

}

void testDocuments::test_case1()
{

}

QTEST_APPLESS_MAIN(testDocuments)

#include "tst_testdocuments.moc"
