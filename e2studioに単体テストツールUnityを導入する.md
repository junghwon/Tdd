# e2studioに単体テストツールUnityを導入する

## 1. プロジェクト
---
### C/C++ projectの作成
    e2studioでC/C++ project（Excutable project）を作成する。
    今回は、コンパイラにgcc for Renesas RXを選択する。
    Configurations"でHardware Debug構成を生成"と"Debug"構成を生成の2つにチェックを入れる。

### コード生成
    スマートコンフィグレータでターゲットボードに合わせたデバイス設定を行う。
    設定を行った後コード生成を実行する。

### コード修正
    src/smc_gen/r_bsp/mcu/rx231/mcu_clocks.cの427行付近の下記の箇所に、コンパイルスイッチ"USE_SIMULATOR"を追加する。
    （シミュレータでは、ハードウェアの変化を無限に待ってしまうため）
```c
        /* Dummy read and compare. cf."5. I/O Registers", "(2) Notes on writing to I/O registers" in User's manual.
           This is done to ensure that the register has been written before the next register access. The RX has a 
           pipeline architecture so the next instruction could be executed before the previous write had finished.
         */
        if(0x00 ==  SYSTEM.HOCOCR.BYTE)
        {
            R_BSP_NOP();
        }

        /* WAIT_LOOP */
#ifndef USE_SIMULATOR
        while(0 == SYSTEM.OSCOVFSR.BIT.HCOVF)
        {
            /* The delay period needed is to make sure that the HOCO has stabilized. */
            R_BSP_NOP();
        }
#endif // USE_SIMULATOR
```
    プロジェクトエクスプローラから、プロパティ>c/c++一般>パスおよびシンボルを選択し、構成をDebugに変更。
    #シンボルタブより、コンパイルスイッチ"USE_SIMULATOR"を追加する。
    また、同様に構成を全ての構成に変更し、コンパイルスイッチ"UNITY_FIXTURE_NO_EXTRAS"を追加する。

### デバッグ準備
#### ・HardwareDebug
    メニュー>実行>デバッグの構成より、HardwareDegubの構成を選択し、ターゲットに合わせて設定を行う。
#### ・Debug
    同様にDebugの構成を選択し、Debug構成を設定する。（特に変更なし）

### デバッグ確認
    ビルド後デバッグを実行しする。
    Printfデバッグができる様に、メニュー>Renesas View>デバッグから、Renesas Debug Virtual Consoleを表示する。
<br>

## 2. 単体テストフレームワークUnityの導入
---
### Unityのダウンロード
    以下のgithubリポジトリより、Unityのソースをダウンロードする。
    https://github.com/ThrowTheSwitch/Unity

### e2studioプロジェクトにソース格納用フォルダを追加
    ファルダ構成を以下のとおり変更する。
    src/
        - smc_gen/      // ルネサスの自動生成コード
        - test/         // テストファイルを格納する（追加）
        - unity/        // Unityのソースを格納する（追加）

### Unityソースをフォルダに格納する
    作成したフォルダ/src/unityに以下のソースを追加する。
    ・Unity-master/src
        unity.c, unity.h, unity_internals.h
    ・Unity-master/extras/fixture/src
        unity_fixture.c, unity_fixture.h, unity_fixture_intarnals.h
<br>

## 3. テストの実行
### テストファイル
    下記の様なテストファイル"Test0.c"を作成し、/src/testに格納する。
    "Test0"はテストグループ名であり、自由な名前に設定する。
    "testAdd"はテストケース名であり、自由な名前に設定する。
```c : Test0.c
#include "../unity/unity_fixture.h"

// テストグループを定義
TEST_GROUP(Test0);

// 各テストケースの前に実行する共通処理(初期化)
TEST_SETUP(Test0)
{
}

// 各テストケースの後に実行する共通処理(後片付け)
TEST_TEAR_DOWN(Test0)
{
}

// テストケース
TEST(Test0, testAdd)
{
    TEST_FAIL_MESSAGE("This test always fails.");
}

// テストグループで、実行するテストケースを列挙する
// 上で作ったテストケースTest0, testAddをRUN_TEST_CASEに指定する
TEST_GROUP_RUNNER(Test0)
{
    RUN_TEST_CASE(Test0, testAdd);
}
```
    更にAllTests.cを作成し、Test0グループを実行する。
```c : AllTests.c
#include "../unity/unity_fixture.h"

// 実行するテストグループを列挙する
void RunAllTests(void)
{
    RUN_TEST_GROUP(Test0);
}
```

### main関数からテストを呼ぶ
    main関数からテストを呼ぶ。
    UnityMain()にはコマンドラインオプションが指定できる。ここでは"-v"を渡し、各テストの実行前にテスト名を出力しる。
```c
#include "r_smc_entry.h"
#include "unity/unity_fixture.h"

void main(void)
{
#if 1
    // コマンドラインオプション "-v" を指定。
    // -v   詳細(verbose)モード。各テストの実行前にテスト名を出力する。
    int argc = 2;
    const char *argv[] = {"program name", "-v"};
    extern void RunAllTests(void);
    UnityMain(argc, argv, RunAllTests);
#endif

    while(1);
}
```

### 実行する
    ビルド、デバッグ実行するとRenasas Debug Virtual Consoleにテスト結果が表示される。
