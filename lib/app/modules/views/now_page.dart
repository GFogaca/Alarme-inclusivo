import 'dart:async';
import 'package:flutter/material.dart';
import 'package:flutter_alarm_clock/app/data/theme_data.dart';
import 'package:intl/intl.dart';
import 'package:flutter_alarm_clock/controllers/esp8266_controller.dart';

import 'clockview.dart';

class NowPage extends StatefulWidget {
  @override
  _NowPageState createState() => _NowPageState();
}

class _NowPageState extends State<NowPage> {
  bool pressionado = false;
  String textoBotao = 'TOCAR AGORA';

  void alternarBotao() {
    setState(() {
      pressionado = !pressionado;
      textoBotao = pressionado ? 'PARAR ALARME' : 'TOCAR AGORA';
      if (pressionado == true) {
        Esp8266Controller.enviarComando('ligar');
      } else if (pressionado == false) {
        Esp8266Controller.enviarComando('desligar');
      }
    });
  }

  @override
  Widget build(BuildContext context) {
    return Container(
      padding: EdgeInsets.symmetric(horizontal: 32, vertical: 64),
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        crossAxisAlignment: CrossAxisAlignment.start,
        children: <Widget>[
          Flexible(
            flex: 1,
            fit: FlexFit.tight,
            child: Text(
              'Now',
              style: TextStyle(
                  fontFamily: 'avenir',
                  fontWeight: FontWeight.w700,
                  color: CustomColors.primaryTextColor,
                  fontSize: 24),
            ),
          ),
          Flexible(
            flex: 10,
            fit: FlexFit.tight,
            child: SizedBox.expand(
                child: FloatingActionButton.large(
              onPressed: () => alternarBotao(),
              backgroundColor: pressionado ? Colors.green : Colors.red,
              heroTag: null,
              child: Text(textoBotao,
                  style: const TextStyle(color: Colors.white, fontSize: 20.0),
                  textAlign: TextAlign.center),
            )),
          )
        ],
      ),
    );
  }
}
