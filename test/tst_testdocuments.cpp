#include <QtTest>

#include "../Plan-Describer/document.hpp"
#include "../Plan-Describer/documenttablesaggregate.hpp"
// add necessary includes here

class testDocuments : public QObject
{
    Q_OBJECT

public:
    testDocuments();
    ~testDocuments();

private slots:
    void test_case1();
    void test_case2();

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

void testDocuments::test_case2()
{
    DocumentTablesAggregate *object = new DocumentTablesAggregate("database.db3");
    object->loadData();
    QCOMPARE(object->variants().count(),3);
}

QTEST_APPLESS_MAIN(testDocuments)

#include "tst_testdocuments.moc"
