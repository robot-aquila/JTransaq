pipeline {
    agent {
        label 'windows-msbuild'
    }
    stages {
        stage('Build.DLL') {
            bat 'msbuild JTransaq/JTransaq.sln /t:Clean;Build /p:Configuration=Release'
        }
        stage('Build.JAR') {
            bat 'mvn -B -f JTransaq -DskipTests clean package'
        }
        stage('Test.JAR') {
            bat 'mvn -B -f JTransaq test'
        }
    }
}
