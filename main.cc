if (strstr(imagefilename, "dwm.exe"))
			{
				int a = 1;

				DbgBreakPoint();
				DWORD64 ImageBase = 0;
				CONTEXT ContextRecord;
				PRUNTIME_FUNCTION FunctionEntry = nullptr;
				RtlCaptureContext(&ContextRecord);
				while ((Index < 256) && (ContextRecord.Rip != 0))
				{
					FunctionEntry = RtlLookupFunctionEntry(ContextRecord.Rip,
					&ImageBase,
					NULL);
					if ((FunctionEntry != NULL))
					{
						RtlVirtualUnwind(0,
							(ULONG64)ImageBase2.ModuleBase,
							ContextRecord.Rip,
							FunctionEntry,
							&ContextRecord,
							&HandlerData,
							&EstablisherFrame,
							NULL);
						ULONG64 *p = (ULONG64*)((ULONG64)ContextRecord.Rsp - 8);
						ULONG64 test12345 = *p;
						if (test12345 == 0x00000)
						{
							*p = 0x123456789;
							break;
						}
						DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "%llx\n", test12345);
						//std::cout << std::hex<< test12345 << std::endl;

					}
					else {
						break;
					}
				}

			}