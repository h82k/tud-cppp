#
# Copies the exercise sheets from the tex projects to this folder
#

$days= "tag1","tag2","tag3","tag4","tag5","tag6"

ForEach($day in $days) {
    echo "Copying $day.pdf"
    copy "./sources/$day/$day.pdf" .
}



