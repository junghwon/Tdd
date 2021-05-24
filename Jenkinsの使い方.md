# Jenkinsの使い方　(Windows)

## 参考サイト
・JenkinsでGitにPush時に自動ビルドさせる<br>
<https://simple-it-life.com/2016/03/23/jenkins-push/><br>
・Jenkins study<br>
<https://www.slideshare.net/atotto/jenkins-study720130128><br>
・JenkinsでEclipse CDT (C++) プロジェクトをビルドする<br>
<https://atotto.hatenadiary.jp/entry/2013/01/28/183550><br>
<br>

## 準備：e2studioのプロジェクトをコマンドラインでビルドする（Headless build）
### 1. JDKのインストール
    JDKをインストールする。

### 2. eclipse.iniファイルの作成
    \Renesas\e2_studio\eclipseディレクトリ内のe2studio.iniを複製する。
    複製したファイルの名前をeclipse.iniに変える。

### 3. ビルド実行
    コマンドプロンプトから
    \Renesas\e2_studio\eclipseディレクトリに移動し以下を実行する。
    -dataにはワークスペースを指定し、-importにはプロジェクトを指定する。
```shell
eclipsec.exe -nosplash --launcher.suppressErrors -debug -consolelog -application org.eclipse.cdt.managedbuilder.core.headlessbuild -data "C:\Users\junghwon\e2_studio\workspace" -import "C:\Users\junghwon\e2_studio\workspace\headlessTest" -build all
```
<br>

## Jenkinsのダウウンロードとインストール
### 1. Jenkinsのダウンロード
    下記公式サイトからJenkinsをダウンロードする。
    LTSのWinddowsを選択する。
    https://www.jenkins.io/

### 2. インストール
* Service Logon Credentials : "Run service as LocalSystem"を選択する。<br>
* Port Number : デフォルト"8080"を使用する。<br>
* Java home directory : JDKまたはJREのディレクトリを指定する。<br>
* Contam Setup : そのままでOK<br>
<br>

## Jenkinsの初期セットアップ
### 1. 初期パスワードの確認
    インストールが完了するとJenkinsがブラウザで立ち上がる。
    下記のように、初期パスワードが記載されているディレクトリパスが表示されるので、そこに初期パスワードを見に行く。

    C:\Windows\system32\config\systemprofile\AppData\Local\Jenkins\.jenkins\secrets\initialAdminPassword

### 2. ログイン
    初期パスワードを入力してログインする。

### 3. プラグインのインストール
    "Install suggester plugins"を選択すると、プラグインのインストールが始まる。

### 4. ユーザー名とパスワードの設定
    ユーザー名とパスワード等を設定する。

### 5. URLの設定
    今回は下記の通り設定する。
    http://localhost/jenkins:8080/
    
<br>

## ジョブの作成
### 1. ジョブの作成
    Enter an item nameの欄に新規にジョブ名をつけ、フリースタイル・プロジェクトのビルドを選択する。

### 2. ビルド設定
    ビルドタブを選択し、ビルド手順の追加から"windowsバッチコマンドの実行"を選択する。
    コマンドの欄に以下を記載する。
    保存を押して設定を保存する。
```c
C:\Renesas\e2_studio\eclipse\eclipsec.exe -nosplash --launcher.suppressErrors -debug -consolelog -application org.eclipse.cdt.managedbuilder.core.headlessbuild -data "C:\Users\junghwon\e2_studio\workspace" -import "C:\Users\junghwon\e2_studio\workspace\headlessTest" -build all
```

### 3. ビルドの実行
    ジョブページに入って、"ビルド実行"を押す。
<br>

## リモートからジョブの実行
### 1. 基本
    基本的には以下の感じで実行できる。
```shell
curl http://[jenkins-server]:8080/job/[job_name]/build
```
<br>

## Git連携



    
