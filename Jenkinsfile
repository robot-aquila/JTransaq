pipeline {
    agent {
        label 'windows-msbuild'
    }
    stages {
        stage('Prepare') {
            steps {
                bat 'set'
            }
        }
        stage('Build.DLL') {
            steps {
                bat 'msbuild JTransaq/JTransaq.sln /t:Clean;Build /p:Configuration=Release'
            }
        }
        stage('Build.JAR') {
            steps {
                bat 'mvn -B -f JTransaq -DskipTests clean package'
            }
        }
        stage('Test.JAR') {
            steps {
                bat 'mvn -B -f JTransaq test'
            }
        }
    }
}
