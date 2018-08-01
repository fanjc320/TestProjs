#!/bin/bash


echo "-----------begin--------------"

echo "game.log >> game3.log "

grep "BagExpand" game.log|tail -n 5 >> game3.log
grep "ElementSkill" game.log|tail -n 5 >> game3.log
grep "EquipmentFlow" game.log|tail -n 5 >> game3.log
grep "ExchangeLog" game.log|tail -n 5 >> game3.log
grep "GemFlow" game.log|tail -n 5 >> game3.log
grep "GuajiFlow" game.log|tail -n 5 >> game3.log
grep "GuildBoss" game.log|tail -n 5 >> game3.log
grep "GuildFlow" game.log|tail -n 5 >> game3.log
grep "GuildRedBag" game.log|tail -n 5 >> game3.log
grep "IDIPFlow" game.log|tail -n 5 >> game3.log
grep "KnightFlow" game.log|tail -n 5 >> game3.log
grep "SealCardFlow" game.log|tail -n 5 >> game3.log
grep "SnsFlow" game.log|tail -n 5 >> game3.log
grep "ZjSkillLog" game.log|tail -n 5 >> game3.log
grep "EquipmentFlow" game.log|tail -n 5 >> game3.log


echo "secure.log >> game3.log "

grep "SecBattleFlow" secure.log|tail -n 5 >> game3.log
grep "SecBlackListFlow" secure.log|tail -n 5 >> game3.log
grep "SecBusinessShopDealFlow" secure.log|tail -n 5 >> game3.log
grep "SecBusinessShopShowFlow" secure.log|tail -n 5 >> game3.log
grep "SecPlayerAddFriend" secure.log|tail -n 5 >> game3.log
grep "SecPlayerData" secure.log|tail -n 5 >> game3.log
grep "SecTalkFlow" secure.log|tail -n 5 >> game3.log
grep "SecUICComplainFlow" secure.log|tail -n 5 >> game3.log

echo "-----------end-------------"
