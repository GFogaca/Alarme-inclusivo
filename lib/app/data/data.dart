import 'package:flutter/material.dart';
import 'package:flutter_alarm_clock/app/data/enums.dart';
import 'package:flutter_alarm_clock/app/data/models/alarm_info.dart';
import 'package:flutter_alarm_clock/app/data/models/menu_info.dart';

List<MenuInfo> menuItems = [
  MenuInfo(MenuType.clock,
      title: 'Clock', imageSource: 'assets/clock_icon.png'),
  MenuInfo(MenuType.alarm,
      title: 'Alarm', imageSource: 'assets/alarm_icon.png'),
  MenuInfo(MenuType.now, title: 'Now', imageSource: 'assets/timer_icon.png'),
  MenuInfo(MenuType.info,
      title: 'Info',
      imageSource: 'assets/information_icon.png',
      text:
          'Aplicativo despertador para auxiliar as pessoas na qualidade de vida\n'),
];

List<AlarmInfo> alarms = [
  AlarmInfo(
      alarmDateTime: DateTime.now().add(Duration(hours: 1)),
      title: 'Office',
      gradientColorIndex: 0),
  AlarmInfo(
      alarmDateTime: DateTime.now().add(Duration(hours: 2)),
      title: 'Sport',
      gradientColorIndex: 1),
];
