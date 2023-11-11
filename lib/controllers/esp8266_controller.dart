import 'package:http/http.dart' as http;

class Esp8266Controller {
  static const String esp8266IP = '192.168.15.100';

  static Future<void> enviarComando(String comando) async {
    try {
      var response = await http.post(
        Uri.parse('http://$esp8266IP/comando'),
        body: {'comando': comando},
      );

      if (response.statusCode == 200) {
        print('Comando enviado com sucesso: $comando');
      } else {
        print(
            'Falha ao enviar o comando: $comando. Código de status: ${response.statusCode}');
      }
    } catch (e) {
      print('Erro ao enviar o comando: $e');
    }
  }

  static Future<void> configurarHorario(int hora, int minuto) async {
    try {
      var response = await http.get(
        Uri.parse(
            'http://$esp8266IP/configurar-horario?hora=$hora&minuto=$minuto'),
      );

      if (response.statusCode == 200) {
        print('Horário configurado com sucesso: $hora:$minuto');
      } else {
        print(
            'Falha ao configurar o horário: $hora:$minuto. Código de status: ${response.statusCode}');
      }
    } catch (e) {
      print('Erro ao configurar o horário: $e');
    }
  }
}
