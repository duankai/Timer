Timer
=====

Timer in Windows


You can use like this:

void main()
{
	Timer * pcTimer = new Timer();
	if (!pcTimer)
	{
		return;
	}

	if (pcTimer->GetInstanceStatus() == INVILID_TIMER_INSTANCE)
	{
		return;
	}
	
	for(int i = 0; i< 10; i++)
	{
		pcTimer->SetTimer( /*CLIENT_STATUS_REPORT_INTERVAL*/5000+i*2000, print, (void *)&i);
	}
	
	delete pcTimer;
	}
	
	
	which print is function.
