#include <ntddk.h>
#include <stdlib.h>


void SampleUnload(_In_ PDRIVER_OBJECT DriverObject)
{
	UNREFERENCED_PARAMETER(DriverObject);

	KdPrint(("Simple driver was unloaded.\n"));
}

extern "C"

NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	OSVERSIONINFOW ptr;
	RtlZeroMemory(&ptr, sizeof(ptr));
	ptr.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	int status = RtlGetVersion(&ptr);
	if (status != STATUS_SUCCESS) {
		KdPrint(("Failed to get version\n"));
	}
	KdPrint(("%lu, %lu ,%lu\n", ptr.dwMajorVersion, ptr.dwMinorVersion, ptr.dwBuildNumber));

	DriverObject->DriverUnload = SampleUnload;
	KdPrint(("Sample driver initialized successfully.\n"));
	
	return STATUS_SUCCESS;
}