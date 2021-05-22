# Jenkinsの使い方

## 参考サイト
・JenkinsでGitにPush時に自動ビルドさせる<br>
<https://simple-it-life.com/2016/03/23/jenkins-push/><br>
・Jenkins study<br>
<https://www.slideshare.net/atotto/jenkins-study720130128><br>
・JenkinsでEclipse CDT (C++) プロジェクトをビルドする<br>
<https://atotto.hatenadiary.jp/entry/2013/01/28/183550><br>


## 
### 1. java run timeのインストール
    https://java.com/ja/download/からJava Run Timeをインストールする。


eclipsec.exe -nosplash -debug -consolelog -apprication org.eclipse.cdt.managebuilder.core.headlessbuild -data C:\Users\junghwon\e2_studio\workspace -import [C:\Users\junghwon\git\e2studio_Unity_test] -build all