// #include "logger.h"



// void DumpHeader(FILE* file)
// {
//     fprintf(file, "index,");

//     fprintf(file, "joyLeftX,joyLeftY,");
//     fprintf(file, "joyRightX,joyRightY,");

//     fprintf(file, "flX,flY,frX,frY,blX,blY,brX,brY,");
//     fprintf(file, "aflX,aflY,afrX,afrY,ablX,ablY,abrX,abrY");

//     fprintf(file, "\n");
// }

// int index = 0;
// void DumpLogPacket(LogPacket packet, FILE* file)
// {
//     fprintf(file, "%d,", index++);
//     fprintf(file, "%f,%f,%f,%f", packet.joyLeftX, packet.joyLeftY, packet.joyRightX, packet.joyRightY);

//     // wheel
//     for (int i = 0; i < 4; i++) {
//         if (i > 0) fprintf(file, ",");

//         fprintf(file, "%f,%f", packet.wheelVector[i].x, packet.wheelVector[i].y);
//     }    
    
//     // wheel actual
//     for (int i = 0; i < 4; i++) {
//         if (i > 0) fprintf(file, ",");

//         fprintf(file, "%f,%f", packet.wheelActualVector[i].x, packet.wheelActualVector[i].y);
//     }

//     fprintf(file, "\n");    
// }
