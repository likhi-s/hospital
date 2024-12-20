cmake_minimum_required(VERSION 3.16)

project(Hospital_management_project LANGUAGES C)

add_executable(Hospital_management_project main.c
    patient.h
    patient.c
    doctor.h
    doctor.c
    staff.h
    staff.c
    treatment.h
    treatment.c
    pharmacy.h
    pharmacy.c
    room.h
    room.c)

include(GNUInstallDirs)
install(TARGETS Hospital_management_project
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
