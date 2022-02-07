#include "Math/Jacobian.h"

void jacobian(const Eigen::Matrix<float, 7, 1> q,
              Eigen::Matrix<float, 6, 7> &J) {
    const double q1 = q(0) DEG2RAD;
    const double q2 = q(1) DEG2RAD;
    const double q3 = q(2) DEG2RAD;
    const double q4 = q(3) DEG2RAD;
    const double q5 = q(4) DEG2RAD;
    const double q6 = q(5) DEG2RAD;
    // const double q7 = q(6) DEG2RAD;

    const double x0 = std::cos(q1);
    const double x1 = std::sin(q1);
    const double x2 = std::sin(q2);
    const double x3 = 0.4208*x2;
    const double x4 = std::cos(q3);
    const double x5 = x0*x4;
    const double x6 = 0.0128*x5;
    const double x7 = std::cos(q4);
    const double x8 = x1*x2;
    const double x9 = x7*x8;
    const double x10 = std::cos(q2);
    const double x11 = std::sin(q3);
    const double x12 = x1*x11;
    const double x13 = x10*x12;
    const double x14 = std::sin(q4);
    const double x15 = x0*x11;
    const double x16 = 0.3143*x15;
    const double x17 = x1*x4;
    const double x18 = x10*x17;
    const double x19 = -x16 - 0.3143*x18;
    const double x20 = std::cos(q6);
    const double x21 = -0.2874*x9;
    const double x22 = x15 + x18;
    const double x23 = x14*x22;
    const double x24 = std::sin(q6);
    const double x25 = x13 - x5;
    const double x26 = std::sin(q5);
    const double x27 = 0.2874*x26;
    const double x28 = x14*x2;
    const double x29 = x1*x28;
    const double x30 = -x15 - x18;
    const double x31 = x29 + x30*x7;
    const double x32 = std::cos(q5);
    const double x33 = 0.2874*x32;
    const double x34 = x31*x33;
    const double x35 = 0.4208*x10;
    const double x36 = 0.0128*x15;
    const double x37 = x10*x7;
    const double x38 = 0.3143*x37;
    const double x39 = 0.3143*x5;
    const double x40 = 0.2874*x37;
    const double x41 = 0.2874*x28;
    const double x42 = x2*x27;
    const double x43 = x10*x14;
    const double x44 = x2*x7;
    const double x45 = 0.0128*x12;
    const double x46 = 0.3143*x17;
    const double x47 = x10*x15;
    const double x48 = x17 + x47;
    const double x49 = 0.2874*x20;
    const double x50 = x14*x49;
    const double x51 = x10*x5;
    const double x52 = x12 - x51;
    const double x53 = x33*(-x17 - x47);
    const double x54 = x0*x28;
    const double x55 = 0.3143*x12;
    const double x56 = 0.3143*x51;
    const double x57 = x52*x7;
    const double x58 = x0*x2;
    const double x59 = x58*x7;
    const double x60 = -x12 + x51;
    const double x61 = x14*x60;
    const double x62 = -x59 - x61;
    const double x63 = x24*x33;
    const double x64 = -x54 + x60*x7;
    const double x65 = x26*x64;
    const double x66 = 0.2874*x59;
    const double x67 = 0.2874*x61;
    const double x68 = x26*x48;
    const double x69 = 0.2874*x68;
    const double x70 = x32*x64;
    const double x71 = -x13 + x5;
    const double x72 = x25*x33;
    const double x73 = x22*x7;
    const double x74 = x14*x30;
    const double x75 = x26*x71;
    const double x76 = 0.3143*x44;
    const double x77 = x10*x11;
    const double x78 = 0.3143*x43;
    const double x79 = 0.2874*x44;
    const double x80 = 0.2874*x43;
    const double x81 = x2*x4;
    const double x82 = x11*x28;
    const double x83 = x11*x2;
    const double x84 = x33*x83;
    const double x85 = x28*x4;
    const double x86 = -x37 + x85;
    const double x87 = x4*x44;
    const double x88 = -x43 - x87;
    const double x89 = x23 + x9;
    const double x90 = x29 - x73;
    const double x91 = x43 + x87;

    J << -0.0118*x0 - x1*x3 + 0.0128*x13 + x14*x19 + x20*(x21 - 0.2874*x23) + x24*(x25*x27 + x34) - x6 - 0.3143*x9,
        x0*x35 + x0*x38 + x2*x36 + x20*(x0*x40 - x41*x5) + x24*(x15*x42 + x33*(-x0*x43 - x44*x5)) - x28*x39,
        -x10*x6 + x14*(-x10*x16 - x46) + x24*(x27*x52 + x53*x7) + x45 - x48*x50,
        x20*(-0.2874*x54 - 0.2874*x57) - 0.3143*x54 + x62*x63 + x7*(-x55 + x56),
        x24*(x53 - 0.2874*x65),
        x20*(-x69 + 0.2874*x70) - x24*(x66 + x67),
        0,
        -x0*x3 + 0.0118*x1 + x14*(x55 - x56) + 0.0128*x17 + x20*(-x66 - x67) + x24*(x33*(x54 + x57) + x69) + 0.0128*x47 - 0.3143*x59,
        -x1*x35 - x1*x38 - x2*x45 + x20*(-x1*x40 + x17*x41) + x24*(-x12*x42 + x33*(x1*x43 + x17*x44)) + x28*x46,
        x14*(0.3143*x13 - x39) + 0.0128*x18 + x24*(x22*x27 + x7*x72) + x36 - x50*x71,
        x19*x7 + x20*(0.2874*x29 - 0.2874*x73) + 0.3143*x29 + x63*(-x74 + x9),
        x24*(-x27*x31 + x72),
        x20*(x34 - 0.2874*x75) - x24*(x21 + 0.2874*x74),
        0,
        0,
        x20*(-x4*x80 - x79) + x24*(x27*x77 + x33*(x28 - x37*x4)) - x3 - x4*x78 - x76 + 0.0128*x77,
        x24*(x27*x81 + x7*x84) + x49*x82 + 0.0128*x81 + 0.3143*x82,
        x20*(-x4*x79 - x80) - x4*x76 + x63*x86 - x78,
        x24*(-x27*x88 + x84),
        x20*(x27*x83 + x33*x88) - x24*(x40 - 0.2874*x85),
        0,
        0,
        x1,
        -x58,
        x48,
        x62,
        x32*x48 + x65,
        x20*x62 - x24*(-x68 + x70),
        0,
        x0,
        x8,
        x71,
        x89,
        x26*x90 + x32*x71,
        x20*x89 - x24*(x32*x90 - x75),
        -1,
        0,
        -x10,
        -x83,
        x86,
        -x26*x91 - x32*x83,
        x20*x86 - x24*(x26*x83 - x32*x91);
}