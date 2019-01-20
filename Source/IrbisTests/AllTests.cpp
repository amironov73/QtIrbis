#include "IrbisTests.h"

// Note: This is equivalent to QTEST_APPLESS_MAIN for multiple test classes.
int main(int argc, char** argv)
{
   int status = 0;

   {
      SubFieldTest tmp;
      status |= QTest::qExec(&tmp, argc, argv);
   }

   {
      RecordFieldTest tmp;
      status |= QTest::qExec(&tmp, argc, argv);
   }

   {
      MarcRecordTest tmp;
      status |= QTest::qExec(&tmp, argc, argv);
   }

   {
      ClientQueryTest tmp;
      status |= QTest::qExec(&tmp, argc, argv);
   }

   {
      FileSpecificationTest tmp;
      status |= QTest::qExec(&tmp, argc, argv);
   }

   {
      IrbisDateTest tmp;
      status |= QTest::qExec(&tmp, argc, argv);
   }

   {
      IrbisEncodingTest tmp;
      status |= QTest::qExec(&tmp, argc, argv);
   }

   {
      IrbisFormatTest tmp;
      status |= QTest::qExec(&tmp, argc, argv);
   }

   {
      TextNavigatorTest tmp;
      status |= QTest::qExec(&tmp, argc, argv);
   }

   return status;
}
