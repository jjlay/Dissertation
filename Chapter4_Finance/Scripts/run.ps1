Set-Location -Path C:\Users\jj.lay\source\repos\Dissertation\Chapter4_Finance\Scripts

Write-Output "Making sure we are not ahead..."
C:\Users\jj.lay\AppData\Local\GitHubDesktop\app-2.2.4\resources\app\git\cmd\git push

Write-Output "Committing changes..."
C:\Users\jj.lay\AppData\Local\GitHubDesktop\app-2.2.4\resources\app\git\cmd\git commit -am "Updating"

Write-Output "Pushing changes..."
C:\Users\jj.lay\AppData\Local\GitHubDesktop\app-2.2.4\resources\app\git\cmd\git push

Write-Output "Executing..."
ssh jjlay@192.41.74.238 -i C:\Users\jj.lay\OneDrive\SSH\pod_keys\pod_id_rsa 'cd github/Dissertation/Chapter4_Finance ; git pull ; make'

