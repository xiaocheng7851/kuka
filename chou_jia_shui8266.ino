#define BLINKER_WIFI
#define BLINKER_ESP_SMARTCONFIG
//#define BLINKER_APCONFIG
#include <Blinker.h>
#define BLINKER_PRINT Serial
#define BLINKER_BLE
#define BLINKER_WITHOUT_SSL
int gpio[] = {26, 25, 4, 2}; //抽水、加水、加热棒、补水esp32用26，25,4,2
bool yin_jiao0 = false, yin_jiao1 = false, yin_jiao2 = false, yin_jiao3 = false;
int shi;                 //时间处理
int gang_ti = 14;        //缸体检测D5
int shui_xiang3 = 27;    //高水位检测D6
int shui_xiang2 = 16;    //中水位检测D7
int shui_xiang1 = 17;    //低水位检测D8
int wu_li_kg[] = {12, 13, 5, 23}; //物理开关

bool a = true, b = true, c = true, d = true, e = true;
bool f = true, g = false, h = false, z = true, w = true, x = true;
int Q;
int xing_qi, ji_dian;     //触发星期和时间
bool t = true;
long cc = 60;
int gang_ti_1;
int shui_xiang3_1;
int shui_xiang2_1;
int shui_xiang1_1;

char auth[] = "0129e5c50dbd";
char ssid[] = "TP_LINK_303";
char pswd[] = "xg888888";

bool aa = true;
bool bb = true;

// 新建组件对象
BlinkerButton Button1("k1");     //设置blinkerapp内数据键名
BlinkerButton Button2("k2");
BlinkerButton Button3("k3");
BlinkerButton Button4("k4");
BlinkerButton Button5("k5");
BlinkerButton Button6("k6");
BlinkerButton Button7("k7");
BlinkerButton Button8("k8");
BlinkerButton Button9("k9");
BlinkerButton Button10("k10");
BlinkerButton Button11("k11");
//////////触发星期////////
void button9_callback(const String & state) {
  BLINKER_LOG("get button state:", state);
  xing_qi = xing_qi + 1;
  if (xing_qi > 7) {
    xing_qi = -1;
  }
  Blinker.println(xing_qi);
}
/////////触发时间//////////
void button10_callback(const String & state) {
  BLINKER_LOG("get button state:", state);
  ji_dian = ji_dian + 1;
  if (ji_dian > 24) {
    ji_dian = 0;
  }
  Blinker.println(ji_dian);
}
/////////单次触发/////////
void button11_callback(const String & state) {
  BLINKER_LOG("get button state:", state);
  t = !t;
  Blinker.println(t);
}
void button1_callback(const String & state) {
  BLINKER_LOG("get button state:", state);
  digitalWrite(gpio[0], !digitalRead(gpio[0]));
  Blinker.delay(500);
  if (digitalRead(gpio[0]) == HIGH) {
    Blinker.println("抽水已启动");

  }
  if (digitalRead(gpio[0]) == LOW) {
    Blinker.println("抽水已关闭");

  }
}
void button2_callback(const String & state) {
  BLINKER_LOG("get button state:", state);
  digitalWrite(gpio[1], !digitalRead(gpio[1]));
  Blinker.delay(500);
  if (digitalRead(gpio[1]) == HIGH) {
    Blinker.println("加水已启动");

  }
  if (digitalRead(gpio[1]) == LOW) {
    Blinker.println("加水已关闭");

  }

}
void button3_callback(const String & state) {
  BLINKER_LOG("get button state:", state);
  digitalWrite(gpio[2], !digitalRead(gpio[2]));
  Blinker.delay(500);
  if (digitalRead(gpio[2]) == HIGH) {
    Blinker.println("加热棒开启");


  }
  if (digitalRead(gpio[2]) == LOW) {
    Blinker.println("加热棒关闭");

  }
}

void button8_callback(const String & state) {
  BLINKER_LOG("get button state:", state);
  digitalWrite(gpio[3], !digitalRead(gpio[3]));
  Blinker.delay(500);
  if (digitalRead(gpio[3]) == HIGH) {
    Blinker.println("补水开启");

  }
  if (digitalRead(gpio[3]) == LOW) {
    Blinker.println("补水关闭");

  }
}

///////////////手动定时补水////////////
void button6_callback(const String & state) {
  BLINKER_LOG("get button state:", state);
  digitalWrite(gpio[3], HIGH);
  Blinker.delay(500);
  Blinker.println("补水已开");
  Blinker.delay(cc * 60 * 1000UL);
  Blinker.println("补水已关");
  Blinker.delay(500);
  digitalWrite(gpio[3], LOW);
  delay(500);
  if (digitalRead(gpio[3]) == LOW) {
    digitalWrite(gpio[2], HIGH);
  }
}
//////////自动补水////////////
void button7_callback(const String  & state) {
  BLINKER_LOG("get button state:", state);
  while (true) {
    if (z) {
      digitalWrite(gpio[3], HIGH);
      Blinker.println("补水已启动");
      z = false;
    }
    if (digitalRead(shui_xiang1) == HIGH && w) {
      digitalWrite(gpio[3], LOW);
      Blinker.println("低水位补水已关闭");
      Blinker.delay(500);
      if (digitalRead(gpio[3]) == LOW) {
        digitalWrite(gpio[2], HIGH);
        Blinker.println("加热棒已启动");
      }
      z = true;
      w = false;
      break;
    }
    if (digitalRead(shui_xiang2) == HIGH && x) {
      digitalWrite(gpio[3], LOW);
      Blinker.println("中水位补水已关闭");
      Blinker.delay(500);
      if (digitalRead(gpio[3]) == LOW) {
        digitalWrite(gpio[2], HIGH);
        Blinker.println("加热棒已启动");
      }
      z = true;
      x = false;
      break;
    }
    if (digitalRead(shui_xiang3) == HIGH) {
      digitalWrite(gpio[3], LOW);
      Blinker.println("高水位补水已关闭");
      Blinker.delay(500);
      if (digitalRead(gpio[3]) == LOW) {
        digitalWrite(gpio[2], HIGH);
        Blinker.println("加热棒已启动");
      }
      break;
    }
  }

}
//////////暂停式抽加水////////////
void button4_callback(const String&state) {
  BLINKER_LOG("get button state:", state);
  Q++;
  if (Q == 3) {
    digitalWrite(gpio[2], LOW);
    Blinker.println("加热棒已关");
    Q = 0;
  }

  Serial.println("抽水启动");
  Blinker.println("抽水启动");
  digitalWrite(gpio[0], HIGH);
  Blinker.delay(cc * 60 * 1000UL);
  Serial.println("抽水关闭");
  Blinker.println("抽水关闭");
  digitalWrite(gpio[0], LOW);
  delay(500);
  Serial.println("加水启动");
  Blinker.println("加水启动");
  digitalWrite(gpio[1], HIGH);
  Blinker.delay(cc * 60 * 1000);
  Serial.println("加水关闭");
  Blinker.println("加水关闭");
  digitalWrite(gpio[1], LOW);



}
///////////////水位感应式///////////////
void button5_callback(const String  & state) {
  BLINKER_LOG("get button state:", state);

  while (true) {

    if (a) {
      digitalWrite(gpio[0], HIGH);
      Serial.println("抽水已开启");
      Blinker.println("抽水已启动");
      a = false;
      Blinker.delay(1000);
      if (state == "tap") {
        a = true;
        digitalWrite(gpio[0], LOW);
        Serial.println("get button state");
        break;
      }
    }

    if ((digitalRead(gang_ti) == LOW) && b) {
      digitalWrite(gpio[0], LOW);
      Serial.println("抽水已关闭");
      Blinker.println("抽水已关闭");
      b = false;
      Blinker.delay(1000);
      if (state == "tap") {
        a = true;
        b = true;
        break;
      }
    }


    if ((digitalRead(gpio[0]) == LOW) && f) {
      digitalWrite(gpio[1], HIGH);
      Serial.println("加水已启动");
      Blinker.println("加水已启动");
      f = false;
      Blinker.delay(1000);
      if (state == "tap") {
        a = true;
        b = true;
        f = true;
        digitalWrite(gpio[1], LOW);
        Blinker.println("加水已关闭");
        break;
      }
    }


    if ((digitalRead(shui_xiang3) == LOW) && c) {
      digitalWrite(gpio[1], LOW);
      Serial.println("高位触发，加水关闭");
      Blinker.println("高位触发，加水关闭，跳出程序");
      Blinker.delay(500);
      Blinker.println("水箱剩余三分之二水量");

      a = true;
      b = true;
      c = false;
      f = true;
      g = true;
      break;
    }

    if ((digitalRead(shui_xiang2) == LOW) && d && g) {
      digitalWrite(gpio[1], LOW);
      Serial.println("中位触发，加水关闭");
      Blinker.println("中位触发，加水关闭，跳出程序");
      Blinker.delay(500);
      Blinker.println("水箱剩余三分之一水量");
      Button5.color("#778899");
      d = false;
      a = true;
      b = true;
      f = true;
      h = true;
      break;
    }

    if ((digitalRead(shui_xiang1) == LOW) && e && h) {
      digitalWrite(gpio[1], LOW);
      Serial.println("低位触发，加水关闭");
      Blinker.println("低位触发，加水关闭，跳出程序");
      Blinker.delay(500);
      Blinker.println("水箱剩余零");

      e = false;
      break;
    }
    delay(1000);
  }
  delay(1000);
  Blinker.delay(1000);
}
void control(int num, const String state)
{
  BLINKER_LOG("按键" + String(num) + "状态 : ", state);        //串口打印
  Blinker.delay(160); //延时150ms不能太少标准按键成功率

  if (state == BLINKER_CMD_ON) {              //如果state是on状态
    BLINKER_LOG(String(num) + "设备已打开");                         //串口打印
    digitalWrite(gpio[num], HIGH);
    Set_Butt(num);

  }
  else if (state == BLINKER_CMD_OFF) {       //如果state是off状态
    BLINKER_LOG(String(num) + "设备已关闭");                       //串口打印
    digitalWrite(gpio[num], LOW);
    Reset_Butt(num);

  }
}

void Set_Butt(int num) //on反馈
{
  if (num == 0) {
    Button1.color("#228B22");                  //设置app按键是绿色
    Button1.text(String(num) + "抽水已打开");
    Button1.print("on");
  }
  else if (num == 1) {
    Button2.color("#228B22");                  //设置app按键是绿色
    Button2.text(String(num) + "加水已打开");
    Button2.print("on");
  }
  else if (num == 2) {
    Button3.color("#228B22");                  //设置app按键是绿色
    Button3.text(String(num) + "加热棒已打开");
    Button3.print("on");
  }
  else if (num == 3) {
    Button8.color("#228B22");                  //设置app按键是绿色
    Button8.text(String(num) + "补水打开");
    Button8.print("on");
  }

}

void Reset_Butt(int num) //off反馈
{
  if (num == 0) {
    Button1.color("#778899");                     //设置app按键是灰色
    Button1.text(String(num) + "抽水已关闭");
    Button1.print("off");
  }
  else if (num == 1) {
    Button2.color("#778899");                     //设置app按键是灰色
    Button2.text(String(num) + "加水已关闭");
    Button2.print("off");
  }
  else   if (num == 2) {
    Button3.color("#778899");                     //设置app按键是灰色
    Button3.text(String(num) + "加热棒已关闭");
    Button3.print("off");
  }
  else if (num == 3) {
    Button8.color("#778899");                     //设置app按键是灰色
    Button8.text(String(num) + "补水关闭");
    Button8.print("off");
  }
}
void heartbeat() {

  BLINKER_LOG("心跳包状态同步");
  Blinker.println(cc);
  for (uint8_t o_num = 0; o_num < 5; o_num++)
  {
    if (digitalRead(gpio[o_num]) == HIGH) {
      Set_Butt(o_num);
    }
    else {
      Reset_Butt(o_num);
    }
  }

}
void dataRead(const String & data) {
  BLINKER_LOG("Blinker readString:", data);
  Blinker.vibrate();
  cc = data.toInt();
  uint32_t BlinkerTime = millis();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  BLINKER_DEBUG.stream(Serial);
#if defined(BLINKER_PRINT)
  BLINKER_DEBUG.stream(BLINKER_PRINT);
#endif
  pinMode(gpio[0], OUTPUT);
  digitalWrite(gpio[0], LOW);
  pinMode(gpio[1], OUTPUT);
  digitalWrite(gpio[1], LOW);
  pinMode(gpio[2], OUTPUT);
  digitalWrite(gpio[2], LOW);
  pinMode(gpio[3], OUTPUT);
  digitalWrite(gpio[3], LOW);
  pinMode(gang_ti, INPUT_PULLUP);
  pinMode(shui_xiang3, INPUT_PULLUP);
  pinMode(shui_xiang2, INPUT_PULLUP);
  pinMode(shui_xiang1, INPUT_PULLUP);
  pinMode(wu_li_kg[0], INPUT_PULLUP);
  pinMode(wu_li_kg[1], INPUT_PULLUP);
  pinMode(wu_li_kg[2], INPUT_PULLUP);
  pinMode(wu_li_kg[3], INPUT_PULLUP);
#if (defined(BLINKER_APCONFIG))||(defined(BLINKER_ESP_SMARTCONFIG))
  Blinker.begin(auth);
#else
  Blinker.begin(auth, ssid, pswd);
#endif
  //Blinker.begin(auth, WiFi.SSID().c_str(), WiFi.psk().c_str());
  Button1.attach(button1_callback);//注册按键回调函数
  Button2.attach(button2_callback);
  Button3.attach(button3_callback);
  Button4.attach(button4_callback);
  Button5.attach(button5_callback);
  Button6.attach(button6_callback);
  Button7.attach(button7_callback);
  Button8.attach(button8_callback);
  Button9.attach(button9_callback);
  Button10.attach(button10_callback);
  Button11.attach(button11_callback);
  Blinker.attachData(dataRead);
  Blinker.attachHeartbeat(heartbeat);
  Blinker.setTimezone(8.0);
}


void loop() {
  Blinker.run();
  cc = cc;
  Blinker.delay(1000);
  //int16_t year1 = Blinker.year();   //年
  //int8_t  month1= Blinker.month();  //月
  //int8_t  day1  = Blinker.mday();   //日
  //int16_t yday1 = Blinker.yday();   //已过多少天
  int8_t  wday1 = Blinker.wday();   //星期几0~6
  int8_t  hour1 = Blinker.hour();   //时
  //int8_t  min1  = Blinker.minute();    //分
  //int8_t  sec1  = Blinker.second();    //秒
  shi = hour1 - 8;              //时间处理
  if (t) {
    if (wday1 == xing_qi && shi == ji_dian ) {
      digitalWrite(gpio[3], HIGH);
      Serial.println("补水已启动");
      Blinker.delay(60 * 60 * 1000);
      digitalWrite(gpio[3], LOW);
      Serial.println("补水已关闭");
      t = false;
    }
  }
  if (t) {
    if (wday1 == xing_qi && shi == ji_dian) {
      digitalWrite(gpio[3], HIGH);
      Serial.println("补水已启动");
      Blinker.delay(120 * 60 * 1000);
      digitalWrite(gpio[3], LOW);
      Serial.println("补水已关闭");
      t = false;
    }
  }
  ///////////抽水//////////
  if (digitalRead(wu_li_kg[0]) == LOW && !yin_jiao0) {
    yin_jiao0 = true;

    digitalWrite(gpio[0], !digitalRead(gpio[0]));

    delay(500);
  }
  else if (digitalRead(wu_li_kg[0]) == HIGH && yin_jiao0) {
    yin_jiao0 = false;

  }
  ////////////////加水//////////////
  if (digitalRead(wu_li_kg[1]) == LOW && !yin_jiao1) {
    yin_jiao1 = true;

    digitalWrite(gpio[1], !digitalRead(gpio[1]));

    delay(500);
  }
  else if (digitalRead(wu_li_kg[1]) == HIGH && yin_jiao1) {
    yin_jiao1 = false;

  }
  ///////////////加热棒////////////
  if (digitalRead(wu_li_kg[2]) == LOW && !yin_jiao2) {
    yin_jiao2 = true;

    digitalWrite(gpio[2], !digitalRead(gpio[2]));

    delay(500);
  }
  else if (digitalRead(wu_li_kg[2]) == HIGH && yin_jiao2) {
    yin_jiao2 = false;

  }
  //////////////补水/////////////
  if (digitalRead(wu_li_kg[3]) == LOW && !yin_jiao3) {
    yin_jiao3 = true;

    digitalWrite(gpio[3], !digitalRead(gpio[3]));

    delay(500);
  }
  else if (digitalRead(wu_li_kg[3]) == HIGH && yin_jiao3) {
    yin_jiao3 = false;

  }
  //...
  delay(500);
}
