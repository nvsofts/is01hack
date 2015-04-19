modules_enabler v1.10 by NV

<概要>
IS01用のmodules_disabled無効化+LSM無効化カーネルモジュール。
ベースバンドバージョン01.00.07で動作確認。

<ライセンス>
BSDライセンスです。

<手順>
1.goroh_kun氏のbootkitなどでmodules_enabler.koを起動時にinsmodする
2.モジュールのロード時にLSMが無効化される
3.IS01のrootシェルで/proc/modules_enablerをcatなどで読み込む
  （何も読み込めないが、正常）
4./proc/sys/kernel/modules_disabledが0になっていることを確認する
5.insmodとかで楽しんでください

<正常に動作しない場合>
カーネルの更新により、値が格納されているメモリアドレスが変わっている
可能性があります。
カーネルを逆アセンブル等して正しいメモリアドレスを調べ、modules_enabler.cの
defineされたメモリアドレスにそのアドレスを書き、再ビルドしてください。

<更新履歴>
2010/12/02 : v1.10 : LSM無効化を追加
2010/12/01 : v1.00 : 初版
