# Jenkinsの使い方

## 参考サイト
・JenkinsでGitにPush時に自動ビルドさせる<br>
<https://simple-it-life.com/2016/03/23/jenkins-push/><br>
・Jenkins study<br>
<https://www.slideshare.net/atotto/jenkins-study720130128><br>
・JenkinsでEclipse CDT (C++) プロジェクトをビルドする<br>
<https://atotto.hatenadiary.jp/entry/2013/01/28/183550><br>


## 
### 1. JDKのインストール

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