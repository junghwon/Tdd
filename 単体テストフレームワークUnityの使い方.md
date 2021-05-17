# 単体テストフレームワークUnityの使い方

## コードの種類と用語
---
    ・テスト対象コード：テストされるコード
    ・テストコード：テスト対象コードをテストするのに使うコード
    ・テストケース：テスト内容を記述テストコード
<br>

## テストコードひな形
---
    テストコードのひな形を以下に示す。
    今回はテスト対象コードを"rangeCookModel.c"とする。
    テストコードの名称は"テスト対象コードのファイル名Test"とする。
```c
// コンパイルスイッチ"UNIT_TEST"を追加する
#ifdef UNIT_TEST

// ../unity/unity_fixture.h及び、テスト対象コードのヘッダファイルをインクルードする
#include "../unity/unity_fixture.h"
#include "../rangeCookModelClass.h"

// テストグループを定義
TEST_GROUP(rangeCookModelTest);

// 変数宣言
// テストで共通で使用する変数はここ(TEST_GROUPのあと)で宣言する

// 各テストケースの前に実行する共通処理(初期化)
TEST_SETUP(rangeCookModelTest)
{
}

// 各テストケースの後に実行する共通処理(後片付け)
TEST_TEAR_DOWN(rangeCookModelTest)
{
}

// テストケース
TEST(rangeCookModelTest, alwaysFail)
{
    TEST_FAIL_MESSAGE("This test always fails.");
}

// テストグループで、実行するテストケースを列挙する
TEST_GROUP_RUNNER(rangeCookModelTest)
{
    RUN_TEST_CASE(rangeCookModelTest, alwaysFail);
}

#endif // UNIT_TEST
```
<br>

### TEST_GROUP
    テストグループを定義する。
    テストグループには任意の名前を付ける。

### 変数宣言
    各テストケースで共通に用いる変数は、TEST_GROUPの後に宣言する。

### TEST_SETUP
    テストケース実行前に行う処理を記述する。
    TEST_SETUP()は各テストケースTEST()実行前に毎回呼び出される。

### TEST_TEAR_DOWN
    テストケース実行後に行う処理を記述する。
    TEST_TEAR_DOWN()は各テストケースTEST()実行後に毎回呼び出される。

### TEST
    テストケース。必要に応じて任意に増やすことができる。
    第二引数には、一意のテストケース名を付ける。

### TEST_GROUP_RUNNER
    RUN_TEST_CASE()を用いて、実行するテストケースを列挙する。
<br>

## 使い方
---

### 前準備
    テスト対象の関数がstatic宣言されている場合、テスト関数から呼び出すことが出来ない。
    そのため、以下の様なコンパイルスイッチを用いてテスト時はstatic宣言を外すように設定する。
```c
/* テスト対象コードに記述する */
#ifdef UNIT_TEST
    #define STATIC
#else
    #define STATIC static
#endif // UNIT_TEST
```

### テストグループに名前を付ける
    TEST_GROUP()に任意の名前を付ける。今回はファイル名と同様に"rangeCookModelTest"とする。
```c
TEST_GROUP(rangeCookModelTest);
```

### テスト変数を宣言する
    各テストケースで共通に用いる変数を宣言する。
    今回の例では、rangeCookModelのMocインスタンス（テスト用の偽物変数）を宣言する。
```c
static rangeCookModel_t mocRangeCookModel = {
	state_standby,
	0,
	&cookManager,
	&cookStart,
	&getCookTimer,
};
```

### テストの前処理を記述する
    TEST_SETUP()に各テストケース実行前の共通処理を記述する。
```c
// 各テストケースの前に実行する共通処理(初期化)
TEST_SETUP(rangeCookModelTest)
{
	mocRangeCookModel.state = state_standby;
	mocRangeCookModel.cookTimer = 0;
}
```

### テストの後処理を記述する
    TEST_TEAR_DOWN()に各テストケース実行後の共通処理を記述する。
    今回は後処理は必要ないので何も記述しない。
```c
// 各テストケースの後に実行する共通処理(後片付け)
TEST_TEAR_DOWN(rangeCookModelTest)
{
}
```

### テストケースを記述する
    TEST()にテストケースを記述する。
    テストアサート(TEST_ASSERT_EQUAL()など)を用いてテストを記述する。
    1つのテストケースにテストアサートは1つだけ実装するのが好ましい。
```c
TEST(rangeCookModelTest, stateCook)
{
	mocRangeCookModel.cookTimer = 1;
	stateCook (&mocRangeCookModel, watt_500, mocRangeCookModel.cookTimer);
	TEST_ASSERT_NOT_EQUAL (state_end, mocRangeCookModel.state);
}
```

### TEST_GROUP_RUUNERに追加する
    RUN_TEST_CASEを用いて、作成したテストケースをTEST_GROUP_RUUNERに追加する。
```c
TEST_GROUP_RUNNER(rangeCookModelTest)
{
    RUN_TEST_CASE(rangeCookModelTest, stateCook);
}
```
<br>

## テストアサートの種類
---

### TEST_IGNORE()
    テストケースをスキップする。

### TEST_FAIL()
    テストケースを失敗させる。

### TEST_ASSERT_TRUE( cond )
    条件condがtrueであると期待する。

### TEST_ASSERT_FALSE( cond )
    条件condがfalseであると期待する。

### TEST_ASSERT_EQUAL( expected, actual )
    actual(実行した値) が expected(期待値) と同値であることを期待する。

### TEST_ASSERT_EQUAL_MEMORY( expected, actual, length )
    配列である actual と 配列 expected が length 個一致することを期待する。
    便利だが、当然境界には注意する必要がある。

### TEST_ASSERT_EQUAL_STRING( expected, actual )
    文字列 actual と expected が一致することを期待する。
    文字列は終端しておく。

### TEST_ASSERT_EQUAL_STRING_LEN( expected, actual, len )
    文字列 actual と expected が len 文字一致することを期待する

### TEST_ASSERT_FLOAT_WITHIN( delta, expected, actual )
    単精度実数値 actual と expected が誤差 delta の範囲内であることを期待します。つまり abs( actual - expected ) <= delta。

### TEST_ASSERT_NULL( expression )
    expression が NULL であることを期待する。

### TEST_ASSERT_NOT_NULL( expression )
    expression が NULL で ない ことを期待する。