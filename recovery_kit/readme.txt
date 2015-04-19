recovery_kit v1.30 by NV ◆2DWoI42Bv.

<概要>
OS書き換え実験用にinit.rcなどを調整したrecovery。
/systemに頼ることなく、initramfsだけでshなどが使えます。

<注意>
このソフトウェアが原因で文鎮化などのトラブルが発生しても責任は負いません。

<使用方法>
flash_imageコマンドでboot領域に焼いてください（使用例を参照）
OS入れ替えの実験をするときに、通常起動用のカーネルをrecovery領域に焼いて、/systemを
書き換えれば、実験が行えます。
もし起動しないということがあったとしても、recovery_kitをboot領域に焼いていれば、
リセットするだけでPCからの復旧が可能です。

<使用例>
1.通常使用で、オールリセットによる文鎮化などからの復旧の可能性を少しでも上げたい
→ recovery_kitを使用することで、電源オフからの起動で使用可能なboot領域を活用
boot領域: recovery_kit
recovery領域: 公式のboot領域 or IS01 Hacked Kernel #001などの改造カーネル

2.OS書き換えの実験を行うときに、安全に実験したい
→ recovery_kitを使用することで、実機で起動できないとわかってからでも復旧を可能に
boot領域: recovery_kit
recovery領域: 対象OSのカーネル
system領域: 対象OSの/system

<リカバリメニュー>
リカバリメニューを開くには、左右反転したrecoveryの画像が消えた後、2秒以内に
ホーム+電源を押すと開きます。
ショートカットキーは一度メニューを開かないと使用できません。
リカバリメニューの項目は以下の通りです。

・Boot recovery partition（ショートカットキー: ホーム+戻る）
recovery領域からブートするために再起動します。

・Boot boot partition（ショートカットキー: ホーム+メニュー）
boot領域からブートするために再起動します。

・Enable QXDM（ショートカットキー: Alt+Q）
QXDM接続を有効にします。再起動しても効果は継続します。
PC側に端末を認識させるために必要な操作です。

・Start adbd recovery（ショートカットキー: Alt+A）
adbdを起動します。一度PC側のadbデーモンにofflineと認識されると再認識の作業が
必要です。注意してください。

・Start recovery（ショートカットキー: Alt+R）
Android system recovery utilityを起動します。ホーム+電源の操作が可能です。

左右反転したrecoveryの画像が消えた後、2秒以内にメニューを開いて"操作されなかったり"、
"メニューを開いて"ショートカットキーがキーボードから入力されなかった場合、自動的に
recovery領域からブートするために再起動します。

<対応コマンド>
・sh
・toolbox
・busybox
・mount_system（system領域を/system2にマウントします）
・mount_data（data領域を/dataにマウントします）

<応用>
recovery_kit.imgをばらして、追加のコマンドを入れたりすると面白いかもしれません。

<更新履歴>
2010/12/14 : v1.30 : "Enable QXDM"をリカバリメニューに追加
2010/12/13 : v1.25 : 起動画面変更、adbdを自動起動に戻す（リカバリメニューは変更無し）
2010/12/13 : v1.20 : リカバリメニュー追加
2010/12/11 : v1.10 : カーネル入れ替え、コマンド追加、起動画面変更
2010/12/10 : v1.00 : 初版
