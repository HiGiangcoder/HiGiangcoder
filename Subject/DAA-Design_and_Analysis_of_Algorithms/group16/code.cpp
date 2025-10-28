#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// loi giai
pair<float, float> getNextPoint(float x, float y, int lastBossID) {
  // Khai bao toan cuc
  static bool initialized = false;
  static float centerX = 0.0f, centerY = 0.0f; // tam cua khu vuc dac biet
  static float stepSize = 100.0f;              // do dai moi buoc
  static int ring = 1, side = 0,
             stepOnSide =
                 0; // ring: so luong vong hien tai.
                    //
                    // side: chi so huong luc giac.
                    //
                    // stepOnSide: so luong da di tren 1 canh cua xoan oc
                    // (spiral) so luong buoc de di het mot canh = so thu tu da
                    // giac dang di chuyen (tinh chat cua luc giac)
  static int phase = 1; // 1 = search, 2 = farm
  static pair<float, float> currentTarget = {0.0f, 0.0f};

  static int boss36Count =
      0; // so boss 36 gap gan day - so luong boss id khac 36
  static int boss36Riel = 0; // so luong boss 36 gap gan day (khong bi tru di)
  static const int thresholdBoss36 =
      2; // so luong boss it nhat de xac dinh khu vuc dac biet

  const float rejoinThreshold = max(
      3.0f,
      stepSize *
          0.05f); // neu khoang cach hien tai den khoang cach mong muon xa hon
                  // rejoinThreshold -> coi nhu di xa khoi vi tri ban dau
  const int maxFarmRings = 4; // toi da 4 vong for de farm xung quanh

  // Ham huong luc giac
  // 6 huong di chuyen cua luc giac
  auto hexDir = [](int dir) -> pair<float, float> {
    static const float DEG2RAD = M_PI / 180.0f;
    float angle = 60.0f * dir;
    return {cos(angle * DEG2RAD), sin(angle * DEG2RAD)};
  };

  // neu la lan dau khoi tao
  if (!initialized) {
    initialized = true;
    centerX = x;
    centerY = y;
    currentTarget = {x, y};
    ring = 1;
    side = 0;
    stepOnSide = 0;
    phase = 1;
  }

  // truong hop vua gap boss xong
  if (lastBossID != 0) {
    if (lastBossID == 36) {
      boss36Count++;
      // neu gap nhieu boss 36 lien tiep -> xac dinh khu vuc dac biet
      if (boss36Count >= thresholdBoss36) {

        phase = 2;
        ring = 1;
        side = 0;
        stepOnSide = 0;
        currentTarget = {x, y};

        // dynamic center: center duoc tinh dua tren trung binh cong cua cac
        // boss36 duoc phat hien nam trong o dac biet
        boss36Riel++;
        centerX = centerX / boss36Riel * (boss36Riel - 1) + x / boss36Riel;
        centerY = centerY / boss36Riel * (boss36Riel - 1) + y / boss36Riel;
      } else
        boss36Riel = 0;
    } else {
      // khong phai boss36, giam so luong boss36 -> neu gap nhieu boss khong
      // phai boss36 thi thoat ra khoi khu vuc
      if (phase == 2)
        boss36Count = max(0, boss36Count - 1);
    }
  }

  float dx = x - currentTarget.first;
  float dy = y - currentTarget.second;
  float dist = sqrt(dx * dx + dy * dy);

  if (dist > rejoinThreshold)
    return currentTarget; // neu khoang cach sau khi san quai di qua xa khoi vi
                          // tri muon den thi quay lai vi tri muon den

  // tao diem spiral tiep theo
  auto dirVec = hexDir(side);
  float nx = currentTarget.first + dirVec.first * stepSize;
  float ny = currentTarget.second + dirVec.second * stepSize;

  stepOnSide++;
  if (stepOnSide >=
      ring) { // so luong buoc de di het canh = stt cua luc giac dang di chuyen
              // do do, stepOnSide vuot qua ring -> da di het 1 canh
    stepOnSide = 0;
    side++;
    if (side >= 6) {
      side = 0;
      ring++;
    }
  }

  // neu dang o giai doan farm
  if (phase == 2) {
    float radius =
        sqrt((nx - centerX) * (nx - centerX) +
             (ny - centerY) *
                 (ny - centerY)); // ban kinh tu center den vi tri muon den
    float maxRadius =
        maxFarmRings *
        stepSize; // ban kinh toi da
                  // se co maxFarmRings luc giac deu vong vao nhau,
                  // dinh cach trung tam stepSize don vi
                  // (vi do dai canh luc giac bang canh tu center den dinh)

    // neu ra ria khu farm: quay dan ve trung tam
    if (radius > maxRadius) {
      // chuan hoa vector (dirX, dirY) la vector tu vi tri hien tai den tam
      float dirX = centerX - x;
      float dirY = centerY - y;
      float len = sqrt(dirX * dirX + dirY * dirY) + 1e-6f;
      dirX /= len;
      dirY /= len;

      nx = x + dirX * stepSize * 0.8f; // quay nhe ve tam
      ny = y + dirY * stepSize * 0.8f;
      ring = maxFarmRings;
    }
  }

  currentTarget = {nx, ny};
  return currentTarget;
}

// mo phong boss xung quanh nhan vat
int simulateBoss(float x, float y) {
  // Mo phong 1 vung dac biet (500, 500)
  float distSpecial = sqrt((x - 500) * (x - 500) + (y - 500) * (y - 500));
  bool inSpecial = distSpecial < 400.0f;

  // 20% co hoi gap boss trong moi lan di chuyen
  if (rand() % 100 < 20) {
    // Neu o trong khu vuc dac biet: 50% co hoi la boss co ID = 36
    // Nguoc lai, BossID random [0, 39]
    if (inSpecial)
      return (rand() % 100 < 50) ? 36 : rand() % 40;
    else
      return rand() % 40;
  }
  return 0; // khong gap Boss
}

int main() {
  srand(time(nullptr));

  float x = 0.0f, y = 0.0f;
  float targetX = 0.0f, targetY = 0.0f;
  bool moving = false;
  int lastBossID = 0, bossID = 0;

  cout << fixed << setprecision(1);
  cout << "Bat dau mo phong" << endl;

  for (int t = 0; t < 1000; t++) {
    lastBossID = simulateBoss(x, y);
    bossID = lastBossID;

    if (lastBossID != 0) {
      // tim thay boss
      moving = false;

      float dist = min(50.0f, float(rand() % 51));
      x += dist * ((rand() % 2) ? 1 : -1);
      y += dist * ((rand() % 2) ? 1 : -1);
      cout << "    Killed Boss ID: " << lastBossID << " tai (" << x << ", " << y
           << ")" << endl;
      lastBossID = 0; // sau khi ha boss xong
      continue;
    }

    if (!moving) {
      tie(targetX, targetY) = getNextPoint(x, y, lastBossID);
      moving = true;
      cout << "- Dang di toi (" << targetX << ", " << targetY << endl;
    }

    float dx = targetX - x, dy = targetY - y;
    float dist = sqrt(dx * dx + dy * dy);
    float step = min(30.0f, dist); // moi buoc di 30 don vi
    if (dist > 1e-3) {
      x += step * dx / dist;
      y += step * dy / dist;
    }

    if (dist < 1e-3 || step >= dist) {
      moving = false;
      cout << "- Da toi dich (" << x << ", " << y << ")" << endl;
    }
  }

  cout << "KET THUC MO PHONG" << endl;
  return 0;
}
