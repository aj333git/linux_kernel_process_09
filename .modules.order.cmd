cmd_/home/oem/kernel_process_09/modules.order := {   echo /home/oem/kernel_process_09/thread_showall.ko; :; } | awk '!x[$$0]++' - > /home/oem/kernel_process_09/modules.order
