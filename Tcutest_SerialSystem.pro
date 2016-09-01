######################################################################
# Automatically generated by qmake (2.01a) ?? 9? 1 09:55:53 2016
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . \             
              define \
              main \
              qcom \
              startUp \
              tcu_canbus \
              main/ui \
              qcom/dlt645_2007 \
              qcom/qextserial
INCLUDEPATH += . \
               tcu_canbus \
               main/ui \               
               main \
               startUp \
               qcom \
               qcom/qextserial \
               qcom/dlt645_2007

# Input
HEADERS += global.h \
           myerr_sigals_slots.h \
           mysigals_slots.h \
           mythread.h \           
           define/define.h \
           main/main.h \
           main/secondwindow.h \
           main/test_auto.h \
           main/test_manual.h \
           qcom/Emter_window.h \
           startUp/myevent.h \
           startUp/startUpFrm.h \
           tcu_canbus/error.h \
           tcu_canbus/Hachiko.h \
           tcu_canbus/log.h \
           tcu_canbus/serialsystem.h \
           tcu_canbus/tcu.h \
           main/ui/bat_information.h \
           main/ui/billing_info.h \
           main/ui/charging_end.h \
           main/ui/charging_monitoring.h \
           main/ui/connect_charge.h \
           main/ui/equipment_information.h \
           main/ui/equipment_testing.h \
           main/ui/settlement_inf.h \
           main/ui/suspend_service.h \
           main/ui/tcu_help.h \
           qcom/dlt645_2007/dlt645_api_07.h \
           qcom/qextserial/qextserialport.h \
           qcom/qextserial/qextserialport_global.h \
           qcom/qextserial/qextserialport_p.h
FORMS += qcom/Emter_window.ui \
         startUp/startUpFrm.ui \
         main/ui/bat_information.ui \
         main/ui/billing_info.ui \
         main/ui/charging_end.ui \
         main/ui/charging_monitoring.ui \
         main/ui/connect_charge.ui \
         main/ui/equipment_information.ui \
         main/ui/equipment_testing.ui \
         main/ui/main.ui \
         main/ui/secondwindow.ui \
         main/ui/settlement_inf.ui \
         main/ui/suspend_service.ui \
         main/ui/tcu_help.ui \
         main/ui/test_auto.ui \
         main/ui/test_manual.ui
SOURCES += global.cpp \
           myerr_sigals_slots.cpp \
           mysigals_slots.cpp \
           mythread.cpp \           
           main/main.cpp \
           main/secondwindow.cpp \
           main/test_auto.cpp \
           main/test_manual.cpp \
           qcom/Emter_window.cpp \
           startUp/startup.cpp \
           startUp/startUpFrm.cpp \
           tcu_canbus/Hachiko.c \
           tcu_canbus/log.c \
           tcu_canbus/serialsystem.c \
           tcu_canbus/tcu.c \
           main/ui/bat_information.cpp \
           main/ui/billing_info.cpp \
           main/ui/charging_end.cpp \
           main/ui/charging_monitoring.cpp \
           main/ui/connect_charge.cpp \
           main/ui/equipment_information.cpp \
           main/ui/equipment_testing.cpp \
           main/ui/settlement_inf.cpp \
           main/ui/suspend_service.cpp \
           main/ui/tcu_help.cpp \
           qcom/dlt645_2007/dlt645_api_07.c \
           qcom/dlt645_2007/dlt645_api_test.c \
           qcom/qextserial/qextserialport.cpp \
           qcom/qextserial/qextserialport_unix.cpp
RESOURCES += img.qrc qcom/images.qrc
RC_FILE += qcom/myico.rc
