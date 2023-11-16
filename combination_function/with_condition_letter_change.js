var kondisi = false;
var currentInput = msg.payload['/sarung/kanan'] + msg.payload['/sarung/kiri'];
var previousInput = flow.get('previousInput') || '';

// Ketika tombol ditekan kata terhapus
if (msg.payload == "hapus") {
    // Untuk mengatasi permasalahan setelah dihapus huruf sebelumnya yang serupa tidak dikirim
    msg.payload['/sarung/kanan'] === '-' && msg.payload['/sarung/kiri'] === '-';
}

if (currentInput === previousInput) {
    // Jika input saat ini sama dengan input sebelumnya, tidak mengirimkan payload
} else {
    flow.set('previousInput', currentInput); // Menyimpan input saat ini sebagai input sebelumnya
    
    // Kanan A & Kiri A Output A
    if (msg.payload['/sarung/kanan'] === 'A' && msg.payload['/sarung/kiri'] === 'A') {
        msg.payload = { "Output": "A" };
        kondisi = true;
    }
    // Kanan W & Kiri W Output W
    if (msg.payload['/sarung/kanan'] === 'W' && msg.payload['/sarung/kiri'] === 'W') 
    {
        msg.payload = { "Output": "W" };
        kondisi = true;
    }
    
    // Kanan U & Kiri - Output U
    if (msg.payload['/sarung/kanan'] === 'U' && msg.payload['/sarung/kiri'] === '-') 
    {
        msg.payload = { "Output": "U" };
        kondisi = true;
    }
    
    // Kanan A atau W & Kiri I Output P
    if ((msg.payload['/sarung/kanan'] === 'A' || msg.payload['/sarung/kanan'] === 'W') && msg.payload['/sarung/kiri'] === 'I') 
    {
        msg.payload = { "Output": "P" };
        kondisi = true;
    } 
    
    // Kanan A atau W & Kiri - Output L
    if ((msg.payload['/sarung/kanan'] === 'A' || msg.payload['/sarung/kanan'] === 'W') && msg.payload['/sarung/kiri'] === '-') 
    {
        msg.payload = { "Output": "L" };
        kondisi = true;
    } 
    
    // Kanan I & Kiri - Output I
    if (msg.payload['/sarung/kanan'] === 'I' && msg.payload['/sarung/kiri'] === '-') 
    {
        msg.payload = { "Output": "I" };
        kondisi = true;
    }
    
    // Kanan J & Kiri - Output J
    if (msg.payload['/sarung/kanan'] === 'J' && msg.payload['/sarung/kiri'] === '-') 
    {
        msg.payload = { "Output": "J" };
        kondisi = true;
    }
    
    // Kanan B & Kiri I Output B
    if (msg.payload['/sarung/kanan'] === 'B' && msg.payload['/sarung/kiri'] === 'I') 
    {
        msg.payload = { "Output": "B" };
        kondisi = true;
    }
    
    // Kanan B & Kiri - Output E
    if (msg.payload['/sarung/kanan'] === 'B' && msg.payload['/sarung/kiri'] === '-') 
    {
        msg.payload = { "Output": "E" };
        kondisi = true;
    }
    
    // Kanan C & Kiri - Output C
    if (msg.payload['/sarung/kanan'] === 'C' && msg.payload['/sarung/kiri'] === '-') 
    {
        msg.payload = { "Output": "C" };
        kondisi = true;
    }
    
    // Kanan D & Kiri I Output D
    if (msg.payload['/sarung/kanan'] === 'D' && msg.payload['/sarung/kiri'] === 'I') 
    {
        msg.payload = { "Output": "D" };
        kondisi = true;
    }
    
    // Kanan D & Kiri S Output S
    if (msg.payload['/sarung/kanan'] === 'D' && msg.payload['/sarung/kiri'] === 'S') 
    {
        msg.payload = { "Output": "S" };
        kondisi = true;
    }
    
    // Kanan F atau V & Kiri I Output H
    if ((msg.payload['/sarung/kanan'] === 'F' || msg.payload['/sarung/kanan'] === 'V') && msg.payload['/sarung/kiri'] === 'I') 
    {
        msg.payload = { "Output": "H" };
        kondisi = true;
    } 
    
    // Kanan G & Kiri I Output K
    if (msg.payload['/sarung/kanan'] === 'G' && msg.payload['/sarung/kiri'] === 'I') 
    {
        msg.payload = { "Output": "K" };
        kondisi = true;
    }
    
    // Kanan B & Kiri M Output M
    if (msg.payload['/sarung/kanan'] === 'B' && msg.payload['/sarung/kiri'] === 'M') 
    {
        msg.payload = { "Output": "M" };
        kondisi = true;
    }
    
    // Kanan F atau V & Kiri M Output N
    if ((msg.payload['/sarung/kanan'] === 'F' || msg.payload['/sarung/kanan'] === 'V') && msg.payload['/sarung/kiri'] === 'M') 
    {
        msg.payload = { "Output": "N" };
        kondisi = true;
    } 
    
    // Kanan Q & Kiri Q Output Q
    if (msg.payload['/sarung/kanan'] === 'Q' && msg.payload['/sarung/kiri'] === 'Q') 
    {
        msg.payload = { "Output": "Q" };
        kondisi = true;
    }
    
    // Kanan Q & Kiri _ Output T
    if (msg.payload['/sarung/kanan'] === 'Q' && msg.payload['/sarung/kiri'] === '_') 
    {
        msg.payload = { "Output": "T" };
        kondisi = true;
    }
    
    // Kanan V & Kiri - Output V
    if (msg.payload['/sarung/kanan'] === 'V' && msg.payload['/sarung/kiri'] === '-') 
    {
        msg.payload = { "Output": "V" };
        kondisi = true;
    }
    
    // Kanan F & Kiri - Output F
    if (msg.payload['/sarung/kanan'] === 'F' && msg.payload['/sarung/kiri'] === '-') 
    {
        msg.payload = { "Output": "F" };
        kondisi = true;
    }
    
    // Kanan Q & Kiri X Output X
    if (msg.payload['/sarung/kanan'] === 'Q' && msg.payload['/sarung/kiri'] === 'X') 
    {
        msg.payload = { "Output": "X" };
        kondisi = true;
    }
    
    // Kanan Q & Kiri W Output Y
    if (msg.payload['/sarung/kanan'] === 'Q' && msg.payload['/sarung/kiri'] === 'W') 
    {
        msg.payload = { "Output": "Y" };
        kondisi = true;
    }
    
    // Kanan Z & Kiri - Output Z
    if (msg.payload['/sarung/kanan'] === 'Z' && msg.payload['/sarung/kiri'] === '-') 
    {
        msg.payload = { "Output": "Z" };
        kondisi = true;
    }
    
    // Kanan R & Kiri - Output R
    if (msg.payload['/sarung/kanan'] === 'R' && msg.payload['/sarung/kiri'] === '-') 
    {
        msg.payload = { "Output": "R" };
        kondisi = true;
    }
    
    // Kanan G & Kiri G Output G
    if (msg.payload['/sarung/kanan'] === 'G' && msg.payload['/sarung/kiri'] === 'G') 
    {
        msg.payload = { "Output": "G" };
        kondisi = true;
    }
    
    // Kanan O & Kiri - Output O
    if (msg.payload['/sarung/kanan'] === 'O' && msg.payload['/sarung/kiri'] === '-') 
    {
        msg.payload = { "Output": "O" };
        kondisi = true;
    }
    
    // Kanan V & Kiri - Output V
    if (msg.payload['/sarung/kanan'] === 'V' && msg.payload['/sarung/kiri'] === '-') 
    {
        msg.payload = { "Output": "V" };
        kondisi = true;
    }
    
    if (msg.payload['/sarung/kanan'] === '-' && msg.payload['/sarung/kiri'] === '-') 
    {
        msg.payload = { "Output": "" };
        kondisi = true;
    }
}

if (!kondisi) {
    msg.payload = { "Output": "" };
}

// return msg
return msg;
