#include "Math/Gravity.h"

void gravity(const Eigen::Matrix<float, 7, 1> q, Eigen::Matrix<float, 7, 1>& G)
{
  // Gravity constant [m/s^2]
  const float g = 9.80665;

  const float q1 = q(0) DEG2RAD;
  const float q2 = q(1) DEG2RAD;
  const float q3 = q(2) DEG2RAD;
  const float q4 = q(3) DEG2RAD;
  const float q5 = q(4) DEG2RAD;
  const float q6 = q(5) DEG2RAD;
  const float q7 = q(6) DEG2RAD;

  const float x0 = sin(q1);
  const float x1 = cos(q1);
  const float x2 = sin(q2);
  const float x3 = x2*x2;
  const float x4 = 0.0466477208*x1;
  const float x5 = cos(q2);
  const float x6 = cos(q3);
  const float x7 = 4.4e-5*x5;
  const float x8 = sin(q3);
  const float x9 = x2*x8;
  const float x10 = x2*x6;
  const float x11 = x1*x2;
  const float x12 = 1.1636*x11;
  const float x13 = x0*x6;
  const float x14 = x1*x5;
  const float x15 = x14*x8;
  const float x16 = -x13 - x15;
  const float x17 = x0*x8;
  const float x18 = x14*x6;
  const float x19 = -x17 + x18;
  const float x20 = 0.0064*x5;
  const float x21 = x13 + x15;
  const float x22 = sin(q4);
  const float x23 = x22*x5;
  const float x24 = 0.2084*x6;
  const float x25 = cos(q4);
  const float x26 = x2*x25;
  const float x27 = x25*x6;
  const float x28 = x2*x27;
  const float x29 = x11*x25;
  const float x30 = x19*x22;
  const float x31 = -x29 - x30;
  const float x32 = 0.075478*x22;
  const float x33 = 1.8e-5*x25;
  const float x34 = 1.8e-5*x6;
  const float x35 = 0.075478*x6;
  const float x36 = 0.93*x21;
  const float x37 = 0.015006*x25;
  const float x38 = x10*x22;
  const float x39 = x11*x22;
  const float x40 = x19*x25;
  const float x41 = -x39 + x40;
  const float x42 = 0.93*x41;
  const float x43 = 2.781*x41;
  const float x44 = 0.93*x31;
  const float x45 = cos(q5);
  const float x46 = 0.1059*x23;
  const float x47 = sin(q5);
  const float x48 = x47*x8;
  const float x49 = x27*x45 - x48;
  const float x50 = 0.1059*x2;
  const float x51 = x21*x45;
  const float x52 = x41*x47;
  const float x53 = -x51 - x52;
  const float x54 = 2.103*x53;
  const float x55 = x46*x47;
  const float x56 = x45*x8;
  const float x57 = x27*x47;
  const float x58 = -x56 - x57;
  const float x59 = x21*x47;
  const float x60 = x41*x45;
  const float x61 = -x59 + x60;
  const float x62 = 2.103*x61;
  const float x63 = x23*x47;
  const float x64 = 1.0e-6*x63;
  const float x65 = x23*x45;
  const float x66 = 1.0e-6*x2;
  const float x67 = 0.678*x31;
  const float x68 = 1.0e-6*x25;
  const float x69 = 0.063883*x2;
  const float x70 = 0.678*x53;
  const float x71 = 0.009432*x25;
  const float x72 = 0.009432*x22;
  const float x73 = 0.678*x61;
  const float x74 = sin(q6);
  const float x75 = x25*x74;
  const float x76 = cos(q6);
  const float x77 = x22*x76;
  const float x78 = x45*x77;
  const float x79 = x5*(x75 + x78);
  const float x80 = x22*x74;
  const float x81 = x25*x76;
  const float x82 = x45*x81 - x80;
  const float x83 = -x48*x76 + x6*x82;
  const float x84 = x51 + x52;
  const float x85 = 1.425*x84;
  const float x86 = x56 + x57;
  const float x87 = x31*x74;
  const float x88 = x61*x76;
  const float x89 = x87 + x88;
  const float x90 = 1.425*x89;
  const float x91 = x45*x80;
  const float x92 = x81 - x91;
  const float x93 = x5*x92;
  const float x94 = 0.045483*x2;
  const float x95 = -x45*x75 - x77;
  const float x96 = x48*x74 + x6*x95;
  const float x97 = x2*x96;
  const float x98 = 0.678*x84;
  const float x99 = x31*x76;
  const float x100 = x61*x74;
  const float x101 = -x100 + x99;
  const float x102 = 0.678*x101;
  const float x103 = 0.678*x89;
  const float x104 = cos(q7);
  const float x105 = x104*x75;
  const float x106 = sin(q7);
  const float x107 = x106*x47;
  const float x108 = x104*x45;
  const float x109 = -x107 + x108*x76;
  const float x110 = x109*x22;
  const float x111 = x105 + x110;
  const float x112 = x111*x5;
  const float x113 = x106*x45;
  const float x114 = x104*x47;
  const float x115 = x114*x76;
  const float x116 = x113 + x115;
  const float x117 = -x104*x80 + x109*x25;
  const float x118 = -x116*x8 + x117*x6;
  const float x119 = x118*x2;
  const float x120 = x104*x84;
  const float x121 = x106*x89;
  const float x122 = x120 + x121;
  const float x123 = 0.925*x122;
  const float x124 = x106*x75;
  const float x125 = x113*x76;
  const float x126 = x114 + x125;
  const float x127 = x126*x22;
  const float x128 = x107*x76;
  const float x129 = -x108 + x128;
  const float x130 = x106*x80;
  const float x131 = x126*x25 - x130;
  const float x132 = x106*x84;
  const float x133 = x104*x89;
  const float x134 = -x132 + x133;
  const float x135 = 0.925*x134;
  const float x136 = -x120 - x121;
  const float x137 = 0.925*x136;
  const float x138 = -x114 - x125;
  const float x139 = x138*x22;
  const float x140 = x5*(-x124 + x139);
  const float x141 = x108 - x128;
  const float x142 = x130 + x138*x25;
  const float x143 = x2*(-x141*x8 + x142*x6);
  const float x144 = 0.011402*x5;
  const float x145 = 0.011402*x2;
  const float x146 = 0.5*x101;
  const float x147 = 0.5*x136;
  const float x148 = 0.5*x134;
  const float x149 = x25*x8;
  const float x150 = 0.5795604*x21;
  const float x151 = x22*x8;
  const float x152 = 0.009432*x47;
  const float x153 = 1.0e-6*x45;
  const float x154 = x153*x6 - x48*x68;
  const float x155 = 0.1059*x6;
  const float x156 = 0.1059*x25;
  const float x157 = x155*x45 - x156*x48;
  const float x158 = x155*x47;
  const float x159 = 0.063883*x6;
  const float x160 = x25*x48;
  const float x161 = x8*x82;
  const float x162 = x47*x74;
  const float x163 = 1.0e-6*x162;
  const float x164 = x47*x76;
  const float x165 = 0.045483*x164;
  const float x166 = x8*x95;
  const float x167 = 0.00965*x164;
  const float x168 = 0.045483*x45;
  const float x169 = 0.00965*x162;
  const float x170 = x116*x6;
  const float x171 = x141*x6;
  const float x172 = 0.011402*x8;
  const float x173 = x142*x8;
  const float x174 = x117*x8;
  const float x175 = 0.000281*x162;
  const float x176 = 0.011402*x162;
  const float x177 = x22*x47;
  const float x178 = 1.0e-6*x177;
  const float x179 = 0.063883*x22;
  const float x180 = 0.1509075*x89;
  const float x181 = 0.1509075*x84;
  const float x182 = 0.000281*x76;
  const float x183 = 0.011402*x76;
  const float x184 = x106*x74;
  const float x185 = x104*x74;
  const float x186 = 0.05365*x122;
  const float x187 = 0.029798*x74;
  
  G << g*(1.02561584*x0*x2 - 1.1636*x0*(-0.09958*x2 + x7) - 3.1671e-5*x0 + 0.0237504*x1*x3*x6 + 0.018335052*x1 - 0.7807944*x10*x16 - x102*(0.00965*x2*x83 + x64 + x66*x86 + 0.00965*x79) - x103*(0.045483*x63 + x86*x94 - 0.00965*x93 - 0.00965*x97) + x12*(-0.006641*x10 - 4.4e-5*x9) - x123*(-0.058*x112 - 0.058*x119) - x135*(-0.0615*x140 - 0.0615*x143) - x135*(0.058*x2*(-x129*x8 + x131*x6) + 0.058*x5*(x124 + x127)) - x137*(0.0615*x112 + 0.0615*x119) - x146*(-x111*x144 - x118*x145 + 0.000281*x140 + 0.000281*x143) - x147*(0.029798*x112 + 0.029798*x119 - 0.000281*x93 - 0.000281*x97) - x148*(-0.029798*x140 - 0.029798*x143 + x144*x92 + x145*x96) - 1.1636*x16*(0.117892*x10 - x7) - 3.711*x19*(-x20 + 0.2104*x9) - 1.1636*x19*(0.006641*x5 + 0.117892*x9) - 2.781*x21*(-0.2084*x23 - x24*x26) + x3*x4 - 2.781*x31*(x20*x22 + 0.0064*x28) - x36*(-x2*x22*x34 - x26*x35 - x32*x5 + x33*x5) + x4*x5*x5 - x42*(-x37*x5 + 0.015006*x38 + 0.075478*x9) - x43*(-x20*x25 + 0.0064*x38 + 0.2084*x9) - x44*(0.015006*x23 + 0.015006*x28 - 1.8e-5*x9) - x54*(x45*x46 + x49*x50) - x62*(-x50*x58 + x55) - x67*(-0.009432*x2*x49 - x58*x66 + x64 - 0.009432*x65) - x70*(-1.0e-6*x38 + x49*x69 + x5*x68 + 0.063883*x65) - x73*(-x10*x72 + x5*x71 - x58*x69 + 0.063883*x63) - x85*(-x50*x83 - 0.1059*x79) - x90*(x50*x86 + x55) - x98*(-0.045483*x79 - x83*x94 - 1.0e-6*x93 - 1.0e-6*x97)),
      g*(-x102*(x154 - 0.00965*x161 - x167*x6) - x103*(-0.045483*x160 + 0.00965*x166 + x168*x6 - x169*x6) - 0.0237504*x11*x8 - 5.11984e-5*x11 + x12*(-4.4e-5*x6 + 0.006641*x8) - x123*(0.058*x170 + 0.058*x174) - x135*(0.0615*x171 + 0.0615*x173) - x135*(-0.058*x129*x6 - 0.058*x131*x8) - x137*(-0.0615*x170 - 0.0615*x174) - 1.141487128*x14 - x146*(x117*x172 + 0.011402*x170 - 0.000281*x171 - 0.000281*x173) - x147*(0.000281*x166 - 0.029798*x170 - 0.029798*x174 - x175*x6) - x148*(0.029798*x171 - x172*x95 + 0.029798*x173 + x176*x6) - x149*x150 + 0.0177984*x149*x31 - x157*x62 - x157*x90 + 0.9179735312*x16*x8 - 0.9179735312*x19*x6 - x36*(0.075478*x149 + 1.8e-5*x151) - x42*(-0.015006*x151 + x35) - x43*(-0.0064*x151 + x24) - x44*(-x34 - x37*x8) - x54*(-x156*x56 - x158) - x67*(x152*x6 + x154 + x56*x71) - x70*(1.0e-6*x151 - x159*x47 - 0.063883*x25*x56) - x73*(0.009432*x151 + x159*x45 - 0.063883*x160) - x85*(x158*x76 + 0.1059*x161) - x98*(0.045483*x161 - x163*x6 + x165*x6 + 1.0e-6*x166)),
     g*(-x102*(x178 + 0.00965*x75 + 0.00965*x78) - x103*(0.045483*x177 - 0.00965*x81 + 0.00965*x91) - x123*(-0.058*x105 - 0.058*x110) - 5.11984e-5*x13 - x135*(0.058*x124 + 0.058*x127) - x135*(0.0615*x124 - 0.0615*x139) - x137*(0.0615*x105 + 0.0615*x110) - x146*(-0.011402*x105 - 0.011402*x110 - 0.000281*x124 + 0.000281*x139) - x147*(0.029798*x105 + 0.029798*x110 - 0.000281*x81 + 0.000281*x91) - x148*(0.029798*x124 - 0.029798*x139 + 0.011402*x81 - 0.011402*x91) - 5.11984e-5*x15 + x150*x22 - 0.0160229324*x17 - x177*x180 - 0.2227077*x177*x61 + 0.0160229324*x18 - 0.03175398*x22*x31 - 0.2227077*x22*x45*x53 + 0.03175398*x25*x41 - x36*(-x32 + x33) - x67*(x178 - x45*x72) - x70*(x179*x45 + x68) - x73*(x179*x47 + x71) - x85*(-0.1059*x75 - 0.1059*x78) - x98*(x153*x80 - x168*x77 - 0.045483*x75 - 1.0e-6*x81)),
    g*(-x102*(x153 - x167) - x103*(x168 - x169) - x123*(0.058*x113 + 0.058*x115) - x135*(0.058*x108 - 0.058*x128) - x135*(0.0615*x108 - 0.0615*x128) - x137*(-0.0615*x113 - 0.0615*x115) - x146*(x107*x182 - 0.000281*x108 + 0.011402*x113 + x114*x183) - x147*(-0.029798*x113 - 0.029798*x115 - x175) - x148*(0.029798*x108 - 0.029798*x128 + x176) - x164*x181 - x180*x45 - 1.674e-5*x29 - 1.674e-5*x30 + 0.64975494*x39 - 0.64975494*x40 - 0.266020374*x45*x61 + 0.266020374*x47*x53 - x67*(x152 + x153) - x98*(-x163 + x165)),
    g*(-0.0065427*x101*x74 - 0.1105375*x134*x184 - 0.0568875*x136*x185 - x146*(-0.000281*x184 - 0.011402*x185) - x147*(x104*x187 - x182) - x148*(x106*x187 + x183) + x181*x74 + x185*x186 + 6.78e-7*x51 + 6.78e-7*x52 + 0.006394896*x59 - 0.006394896*x60 + 0.0065427*x76*x89 - x98*(-0.045483*x74 - 1.0e-6*x76)),
    g*(6.78e-7*x100 - 0.1254365*x104*x134 + 0.0717865*x106*x136 - x106*x186 - x146*(-0.000281*x104 + 0.011402*x106) - 0.181744974*x87 - 0.181744974*x88 - 6.78e-7*x99),
    g*(-0.0001405*x120 - 0.0001405*x121 + 0.005701*x132 - 0.005701*x133);
}