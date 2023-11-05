import 'package:flutter/foundation.dart';
import 'package:flutter_alarm_clock/app/data/enums.dart';

class MenuInfo extends ChangeNotifier {
  MenuType menuType;
  String? title;
  String? imageSource;
  String? text;

  MenuInfo(this.menuType, {this.title, this.imageSource, this.text});

  updateMenu(MenuInfo menuInfo) {
    this.menuType = menuInfo.menuType;
    this.title = menuInfo.title;
    this.imageSource = menuInfo.imageSource;
    this.text = menuInfo.text;

//Important
    notifyListeners();
  }
}
