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

## Jenkinsのセットアップ
### 1. 初期パスワードの確認
    インストールが完了するとJenkinsがブラウザで立ち上がる。
    下記のように、初期パスワードが記載されているディレクトリパスが表示されるので、そこに初期パスワードを見に行く。

    C:\Windows\system32\config\systemprofile\AppData\Local\Jenkins\.jenkins\secrets\initialAdminPassword

### 2. ログイン
    初期パスワードを入力してログインする。

### 3. プラグインのインストール
    "Install suggester plugins"を選択すると、プラグインのインストールが始まる。