export module sysinfo;  // DKS: section_5_ex_4 uses example_3.cpp which includes sysinfo module
                        // so alternate module must still be called sysinfo, not sysinfo2
export const char* get_arch();
export const char* get_cpu();
