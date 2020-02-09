#Set-Location -Path C:\Users\jj.lay\source\repos\Dissertation\Chapter4_Finance\Scripts

Write-Output "Committing changes..."
git commit -am "Updating"

Write-Output "Pushing changes..."
git push

Write-Output "Executing..."
ssh jjlay@192.41.74.238 -i C:\Users\jj.lay\OneDrive\SSH\pod_keys\pod_id_rsa 'cd github/Dissertation/Chapter4_Finance ; git pull ; make'

